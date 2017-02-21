#include "Gain.hpp"


Gain::Gain()
{
	mTargetGain = DECIBELS_TO_LINEAR(0.0f);
	Reset();
}


void Gain::Process(float* inbuffer, float* outbuffer, unsigned int length, int channels)
{
	if (mInterpolationSamples)
	{
		float deltaGain = (mTargetGain - mCurrentGain) / mInterpolationSamples;
		while (length)
		{
			if (--mInterpolationSamples)
			{
				mCurrentGain += deltaGain;
				for (int i = 0; i < channels; ++i)
				{
					//*outbuffer++ = *inbuffer++ * (mCurrentGain);
					params.gain = mCurrentGain;
					ApplyDsp(*outbuffer++, *inbuffer++, &params);
				}
			}
			else
			{
				mCurrentGain = mTargetGain;
				break;
			}
			--length;
		}
	}

	unsigned int samples = length * channels;
	while (samples--)
	{
		//*outbuffer++ = *inbuffer++ * (mCurrentGain);
		params.gain = mCurrentGain;
		ApplyDsp(*outbuffer++, *inbuffer++, &params);
	}
}



inline void Gain::ApplyDsp(float inSample, float outSample, GainParams* params)
{
	outSample = inSample * (params->gain);
}



void Gain::Reset()
{
	mCurrentGain = mTargetGain;
	mInterpolationSamples = 0;
}


void Gain::setAmount(float gain)
{
	mTargetGain = DECIBELS_TO_LINEAR(gain);
	mInterpolationSamples = INTERPOLATION_SAMPLES;
}


float Gain::getAmount()
{
	return mCurrentGain;
}
