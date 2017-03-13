#include "Distortion.hpp"

Distortion::Distortion()
{
	mTargetLevel = 1;
	Distortion::Reset();
}

Distortion::~Distortion()
{
}

void Distortion::ProcessAudioBuffer(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	float processLevel = mCurrentLevel;

	if (mInterpolationSamples)
	{
		float deltaGain = (mTargetLevel - mCurrentLevel) / mInterpolationSamples;
		while (length)
		{
			if (--mInterpolationSamples)
			{
				processLevel += deltaGain;
				mCurrentLevel = processLevel;
				for (int i = 0; i < channels; ++i)
				{
					*outBuffer++ = ProcessAudioSample(*inBuffer++);
				}
			}
			else
			{
				processLevel = mTargetLevel;
				break;
			}
			--length;
		}
	}

	unsigned int samples = length * channels;
	while (samples--)
	{
		*outBuffer++ = ProcessAudioSample(*inBuffer++);
	}
	mCurrentLevel = processLevel;
}

/* NOT USED*/
void Distortion::ProcessAudioChannel(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (unsigned int ch = 0; ch < static_cast<unsigned int>(channels); ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, ch);
		}
	}
}

inline float Distortion::ProcessAudioSample(float inSample, unsigned int channel)
{
	float threshold = getLevel();

	// Positive hard clipping
	if (inSample > threshold)
		return threshold;

	// Negative hard clipping
	if (inSample < -threshold)
		return -threshold;

	// No clipping
	return inSample;
}

void Distortion::Reset()
{
	mCurrentLevel = mTargetLevel;
	mInterpolationSamples = 0;
}

float Distortion::getLevel()
{
	return mCurrentLevel;
}

void Distortion::setLevel(float level)
{
	mTargetLevel = level;
	mInterpolationSamples = MathLib::InterpolationSamples;
}

