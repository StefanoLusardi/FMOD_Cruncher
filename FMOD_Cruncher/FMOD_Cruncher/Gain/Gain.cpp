#include "Gain.hpp"

Gain::Gain()
{
	//mTargetAmp = DECIBELS_TO_LINEAR(0.0f);
	mTargetAmp = MathLib::dBToLin(MathLib::ZeroGain_dB);
	Gain::Reset();
}

void Gain::ProcessAudioBuffer(float* inBuffer, float* outBuffer, unsigned int length, int channels)
{	
	float processGain = mCurrentGain;

	if (mInterpolationSamples)
	{
		float deltaGain = (mTargetAmp - mCurrentGain) / mInterpolationSamples;
		while (length)
		{
			if (--mInterpolationSamples)
			{
				processGain += deltaGain;
				for (int i = 0; i < channels; ++i)
				{
					params.gain = processGain;
					*outBuffer++ = ProcessAudioSample(*inBuffer++, &params); // GainParams*
					//*outBuffer++ = ProcessAudioSample(*inBuffer++, &processGain);	// void*
					//ProcessAudioChannel(inBuffer, outBuffer, length, channels);
				}
			}
			else
			{
				processGain = mTargetAmp;
				break;
			}
			--length;
		}
	}

	unsigned int samples = length * channels;
	while (samples--)
	{
		params.gain = processGain;
		*outBuffer++ = ProcessAudioSample(*inBuffer++, &params);		// GainParams*
		//*outBuffer++ = ProcessAudioSample(*inBuffer++, &processGain);	// void*
	}
	mCurrentGain = processGain;
}

/* NOT USED */
void Gain::ProcessAudioChannel(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (unsigned int ch = 0; ch < static_cast<unsigned int>(channels); ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, &params, ch);
		}
	}
}

inline float Gain::ProcessAudioSample(float inSample, GainParams* params, unsigned int /*channel*/)
{
	return inSample * (params->gain);
}

inline float Gain::ProcessAudioSample(float inSample, void * params, unsigned int /*channel*/)
{
	float* gain = static_cast<float*>(params);
	return inSample * (*gain);
}

void Gain::Reset()
{
	mCurrentGain = mTargetAmp;
	mInterpolationSamples = 0;
}

void Gain::setGain(float gain)
{
	//mTargetAmp = DECIBELS_TO_LINEAR(gain);
	mTargetAmp = MathLib::dBToLin(gain);
	mInterpolationSamples = MathLib::InterpolationSamples;
}

float Gain::getGain()
{
	return mCurrentGain;
}
