#include "Distortion.hpp"

Distortion::Distortion()
{
	params = new DistortionParams();
	mTargetLevel = 1;
	Distortion::Reset();
}

Distortion::~Distortion()
{
	delete params;
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
				for (int i = 0; i < channels; ++i)
				{
					params->level = processLevel;
					*outBuffer++ = ProcessAudioSample(*inBuffer++, params);
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
	params->level = processLevel;
	while (samples--)
	{
		*outBuffer++ = ProcessAudioSample(*inBuffer++, params);
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
			*outBuffer++ = ProcessAudioSample(*inBuffer++, params, ch);
		}
	}
}

inline float Distortion::ProcessAudioSample(float inSample, iDspParams * params, unsigned int channel)
{
	float threshold = static_cast<DistortionParams*>(params)->level;

	// Positive hard clipping
	if (inSample > threshold)
		return threshold;

	// Negative hard clipping
	if (inSample  < -threshold)
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

