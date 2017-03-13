#include "Gain.hpp"

Gain::Gain()
{
	mTargetGain = MathLib::dBToLin(MathLib::ZeroGain_dB);
	Gain::Reset();
}

Gain::~Gain()
{
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
				mCurrentGain = processGain;
				for (int i = 0; i < channels; ++i)
				{
					*outBuffer++ = ProcessAudioSample(*inBuffer++); 
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
	while (samples--)
	{		
		*outBuffer++ = ProcessAudioSample(*inBuffer++);		
	}
	mCurrentGain = processGain;
}

/* NOT USED */
void Gain::ProcessAudioChannel(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (int ch = 0; ch < channels; ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, ch);
		}
	}
}

inline float Gain::ProcessAudioSample(float inSample, unsigned int /*channel*/)
{
	return inSample * getGain();
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
