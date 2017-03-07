#include "Noise.hpp"

Noise::Noise()
{
	params = new NoiseParams();
	mTargetAmp = MathLib::ZeroGain_dB;
	Noise::Reset();
}

Noise::~Noise()
{
	delete params;
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
					params->amp = processGain;
					*outBuffer++ = ProcessAudioSample(*inBuffer++, params);		// GainParams*
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
	params->amp = processGain;
	while (samples--)
	{
		*outBuffer++ = ProcessAudioSample(*inBuffer++, params);		
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
			*outBuffer++ = ProcessAudioSample(*inBuffer++, params, ch);
		}
	}
}

inline float Noise::ProcessAudioSample(float inSample, iDspParams * params, unsigned int channel)
{
	return inSample + MathLib::GetRandomFloat() * (static_cast<NoiseParams*>(params)->amp);
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
	mTargetAmp = MathLib::dBToLin(amp);
	mInterpolationSamples = MathLib::InterpolationSamples;
}

