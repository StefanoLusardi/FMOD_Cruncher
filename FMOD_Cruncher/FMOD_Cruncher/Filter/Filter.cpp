#include "Filter.hpp"

Filter::Filter()
{
	params = new FilterParams();
	mTargetCutoff = 5000.0f;
	mTargetResonance = 1.0f;
	Filter::Reset();
}


Filter::~Filter()
{
	delete params;
}

void Filter::ProcessAudioBuffer(float* inBuffer, float* outBuffer, unsigned length, int channels)
{
}

void Filter::ProcessAudioChannel(float* inBuffer, float* outBuffer, unsigned length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (unsigned int ch = 0; ch < static_cast<unsigned int>(channels); ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, params, ch);
		}
	}
}

inline float Filter::ProcessAudioSample(float inSample, iDspParams* params, unsigned channel)
{
	return 0.0f;
}

void Filter::Reset()
{
	mCurrentCutoff = mTargetCutoff;
	mCurrentResonance = mTargetResonance;
	mInterpolationSamples = 0;
}

float Filter::getCutoff()
{
	return mCurrentCutoff;
}

void Filter::setCutoff(float cutoff)
{
	mTargetCutoff = cutoff;
	mInterpolationSamples = MathLib::InterpolationSamples;
}

float Filter::getResonance()
{
	return  mCurrentResonance;
}

void Filter::setResonance(float resonance)
{
	mTargetResonance = resonance;
	mInterpolationSamples = MathLib::InterpolationSamples;
}
