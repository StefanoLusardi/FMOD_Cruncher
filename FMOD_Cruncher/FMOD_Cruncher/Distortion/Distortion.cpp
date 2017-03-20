#include "Distortion.hpp"

Distortion::Distortion()
{
	mTargetLevel  = 1;
	Distortion::Reset();
}

Distortion::~Distortion()
{
	int x = 0;
}

void Distortion::ProcessAudioBuffer(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	float processLevel  = mCurrentLevel;

	if (mInterpolationSamples)
	{
		float deltaGain   = (mTargetLevel  - mCurrentLevel)  / mInterpolationSamples;

		while (length)
		{
			if (--mInterpolationSamples)
			{
				processLevel  += deltaGain;

				mCurrentLevel  = processLevel;

				for (int i = 0; i < channels; ++i)
				{
					*outBuffer++ = ProcessAudioSample(*inBuffer++);
				}
			}
			else
			{
				processLevel  = mTargetLevel;
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
	mCurrentLevel  = processLevel;
}

/* NOT USED*/
void Distortion::ProcessAudioChannel(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (int ch = 0; ch < channels; ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, ch);
		}
	}
}

inline float Distortion::ProcessAudioSample(float inSample, unsigned int /*channel*/)
{
	float threshold = getLevel();
	float sample = inSample;

	// Positive hard clipping
	if (sample > threshold)
		return threshold;

	// Negative hard clipping
	if (sample < -threshold)
		return -threshold;

	// No clipping
	return sample;
}

void Distortion::Reset()
{
	mCurrentLevel  = mTargetLevel;
	mInterpolationSamples = 0;
}

float Distortion::getLevel()
{
	return mCurrentLevel;
}

void Distortion::setLevel(float level)
{
	/* Level value read from the UI is in range [0..1]
	 * Here we perform a mapping from [0..1] to [1..0.25]
	 */
	mTargetLevel = 1 - level * 0.75f;
	mInterpolationSamples = MathLib::InterpolationSamples;
}

