#include "Noise.hpp"

Noise::Noise()
{
	mTargetAmp = DECIBELS_TO_LINEAR(0.0f);
	//mTargetAmp = MathLib::dBToLin(MathLib::ZeroGain_dB);
	Reset();
}

void Noise::ProcessAudioBuffer(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	float processGain = mCurrentAmp;

	if (mInterpolationSamples)
	{
		float deltaGain = (mTargetAmp - mCurrentAmp) / mInterpolationSamples;
		while (length)
		{
			if (--mInterpolationSamples)
			{
				processGain += deltaGain;
				for (int i = 0; i < channels; ++i)
				{
					params.amp = processGain;
					*outBuffer++ = ProcessAudioSample(*inBuffer++, &params);		// GainParams*
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
		params.amp = processGain;
		*outBuffer++ = ProcessAudioSample(*inBuffer++, &params);		// GainParams*
																		//*outBuffer++ = ProcessAudioSample(*inBuffer++, &processGain);	// void*
	}
	mCurrentAmp = processGain;
}

/* NOT USED*/
void Noise::ProcessAudioChannel(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (unsigned int ch = 0; ch < static_cast<unsigned int>(channels); ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, &params, ch);
		}
	}
}

inline float Noise::ProcessAudioSample(float inSample, NoiseParams * params, unsigned int channel)
{
	return inSample + MathLib::GetRandomFloat() * (params->amp);
}

inline float Noise::ProcessAudioSample(float inSample, void * params, unsigned int channel)
{
	float* amp = static_cast<float*>(params);
	return inSample + MathLib::GetRandomFloat() * (*amp);
}

void Noise::Reset()
{
	mCurrentAmp = mTargetAmp;
	mInterpolationSamples = 0;
}

float Noise::getAmp()
{
	return mCurrentAmp;
}

void Noise::setAmp(float amp)
{
	mTargetAmp = DECIBELS_TO_LINEAR(amp);
	mInterpolationSamples = INTERPOLATION_SAMPLES;
}

