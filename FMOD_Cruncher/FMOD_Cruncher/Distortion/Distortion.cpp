#include "Distortion.hpp"

Distortion::Distortion()
{
	params = new DistortionParams();
	mTargetLevel = MathLib::ZeroGain_lin;
	Distortion::Reset();
}

void Distortion::ProcessAudioBuffer(float* inBuffer, float* outBuffer, unsigned length, int channels)
{
	float processLevel = mCurrentLevel;

	if (mInterpolationSamples)
	{
		float deltaGain = (mTargetLevel - mCurrentLevel) / mInterpolationSamples;
		while (length)
		{
			if (--mInterpolationSamples)
			{
				processLevel += deltaGain;
				for (int i = 0; i < channels; ++i)
				{
					params->level = processLevel;
					*outBuffer++ = ProcessAudioSample(*inBuffer++, static_cast<DspParams*>(params));		// GainParams*
					//*outBuffer++ = ProcessAudioSample(*inBuffer++, &processLevel);	// void*
					//ProcessAudioChannel(inBuffer, outBuffer, length, channels);
				}
			}
			else
			{
				processLevel = mTargetLevel;
				break;
			}
			--length;
		}
	}

	unsigned int samples = length * channels;
	while (samples--)
	{
		params->level = processLevel;
		*outBuffer++ = ProcessAudioSample(*inBuffer++, static_cast<DspParams*>(params));		// GainParams*
		//*outBuffer++ = ProcessAudioSample(*inBuffer++, &processLevel);	// void*
	}
	mCurrentLevel = processLevel;
}

/* NOT USED*/
void Distortion::ProcessAudioChannel(float* inBuffer, float* outBuffer, unsigned length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (unsigned int ch = 0; ch < static_cast<unsigned int>(channels); ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, &params, ch);
		}
	}
}

inline float Distortion::ProcessAudioSample(float inSample, DspParams* params, unsigned channel)
{
	float threshold = static_cast<DistortionParams*>(params)->level;

	// Positive hard clipping
	if (inSample > threshold)
		return threshold;

	// Negative hard clipping
	if (inSample  < -threshold)
		return -threshold;

	// No clipping
	return inSample;
}

inline float Distortion::ProcessAudioSample(float inSample, void* params, unsigned channel)
{
	float* threshold = static_cast<float*>(params);
	
	// Positive hard clipping
	if (inSample > *threshold) 
		return *threshold;
	
	// Negative hard clipping
	if (inSample  < -(*threshold)) 
		return -(*threshold);

	// No clipping
	return inSample;
}

void Distortion::Reset()
{
	mCurrentLevel = mTargetLevel;
	mInterpolationSamples = 0;
}

float Distortion::getLevel()
{
	return mCurrentLevel;
}

void Distortion::setLevel(float level)
{
	mTargetLevel = level;
	mInterpolationSamples = MathLib::InterpolationSamples;
}

