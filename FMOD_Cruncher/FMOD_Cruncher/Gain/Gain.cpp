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
					params.gain = mCurrentGain;
					ApplyDsp(*outbuffer++, *inbuffer++, &params);		// void*
					//ApplyDsp(*outbuffer++, *inbuffer++, &mCurrentGain); // GainParams*
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
		params.gain = mCurrentGain;
		ApplyDsp(*outbuffer++, *inbuffer++, &params);		// void*
		//ApplyDsp(*outbuffer++, *inbuffer++, &mCurrentGain); // GainParams*
	}
}

inline void Gain::ApplyDsp(float inSample, float outSample, GainParams* params)
{
	outSample = inSample * (params->gain);
}

inline void Gain::ApplyDsp(float inSample, float outSample, void * params)
{
	float* gain = static_cast<float*>(params);
	outSample = inSample * (*gain);
}

void Gain::Reset()
{
	mCurrentGain = mTargetGain;
	mInterpolationSamples = 0;
}

void Gain::setGain(float gain)
{
	mTargetGain = DECIBELS_TO_LINEAR(gain);
	mInterpolationSamples = INTERPOLATION_SAMPLES;
}

float Gain::getGain()
{
	return mCurrentGain;
}
