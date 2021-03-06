#include "Gain.hpp"

Gain::Gain()
{
	params = new GainParams();
	mTargetGain = MathLib::dBToLin(MathLib::ZeroGain_dB);
	Gain::Reset();
}

Gain::~Gain()
{
	delete params;
}

void Gain::ProcessAudioBuffer(float* inBuffer, float* outBuffer, unsigned int length, int channels)
{	
	float processGain = mCurrentGain;

	if (mInterpolationSamples)
	{
		float deltaGain = (mTargetGain - mCurrentGain) / mInterpolationSamples;
		while (length)
		{
			if (--mInterpolationSamples)
			{
				processGain += deltaGain;
				for (int i = 0; i < channels; ++i)
				{
					params->gain = processGain;
					*outBuffer++ = ProcessAudioSample(*inBuffer++, params); 
				}
			}
			else
			{
				processGain = mTargetGain;
				break;
			}
			--length;
		}
	}

	unsigned int samples = length * channels;
	params->gain = processGain;
	while (samples--)
	{		
		*outBuffer++ = ProcessAudioSample(*inBuffer++, params);		
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
			*outBuffer++ = ProcessAudioSample(*inBuffer++, params, ch);
		}
	}
}

inline float Gain::ProcessAudioSample(float inSample, iDspParams* params, unsigned int /*channel*/)
{
	return inSample * (static_cast<GainParams*>(params)->gain);
}

void Gain::Reset()
{
	mCurrentGain = mTargetGain;
	mInterpolationSamples = 0;
}

void Gain::setGain(float gain)
{
	mTargetGain = MathLib::dBToLin(gain);
	mInterpolationSamples = MathLib::InterpolationSamples;
}

float Gain::getGain()
{
	return mCurrentGain;
}
