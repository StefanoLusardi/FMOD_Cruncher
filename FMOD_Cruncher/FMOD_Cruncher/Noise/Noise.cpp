#include "Noise.hpp"

Noise::Noise()
{
	mTargetAmp = DECIBELS_TO_LINEAR(0.0f);
	Reset();
}

void Noise::ProcessAudioBuffer(float* inBuffer, float* outBuffer, unsigned length, int channels)
{
}

/* NOT USED*/
void Noise::ProcessAudioChannel(float* inBuffer, float* outBuffer, unsigned length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (unsigned int ch = 0; ch < static_cast<unsigned int>(channels); ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, &params, ch);
		}
	}
}

float Noise::ProcessAudioSample(float inSample, NoiseParams* params, unsigned channel)
{
	return inSample * (params->amp);
}

float Noise::ProcessAudioSample(float inSample, void* params, unsigned channel)
{
	float* amp = static_cast<float*>(params);
	return inSample * (*amp);
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

