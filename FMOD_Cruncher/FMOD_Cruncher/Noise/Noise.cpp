#include "Noise.hpp"

Noise::Noise()
{
	mTargetAmp = MathLib::ZeroGain_dB;
	Noise::Reset();
}

Noise::~Noise()
{
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
				mCurrentAmp = processGain;
				for (int i = 0; i < channels; ++i)
				{
					*outBuffer++ = ProcessAudioSample(*inBuffer++);
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
		*outBuffer++ = ProcessAudioSample(*inBuffer++);		
	}
	mCurrentAmp = processGain;
}

/* NOT USED*/
void Noise::ProcessAudioChannel(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (int ch = 0; ch < channels; ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, ch);
		}
	}
}

inline float Noise::ProcessAudioSample(float inSample, unsigned int /*channel*/)
{
	return inSample + MathLib::GetRandomFloat() * getAmp();
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

