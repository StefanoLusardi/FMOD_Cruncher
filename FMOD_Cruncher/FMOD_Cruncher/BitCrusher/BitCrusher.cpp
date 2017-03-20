#include "BitCrusher.hpp"

BitCrusher::BitCrusher()
{
	mBits = 16;
	mDecimation = 1;
	mQuantizationSteps = 1 << mBits;
	BitCrusher::Reset();
}

BitCrusher::~BitCrusher()
{
}

void BitCrusher::ProcessAudioBuffer(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	unsigned int samples = length * channels;
	while (samples--)
	{
		*outBuffer++ = ProcessAudioSample(*inBuffer++);
	}
}

/* NOT USED */
void BitCrusher::ProcessAudioChannel(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (int ch = 0; ch < channels; ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, ch);
		}
	}
}

inline float BitCrusher::ProcessAudioSample(float inSample, unsigned int /*channel*/)
{ 
	mPhasor += getDecimation();

	if (mPhasor >= 1.0f)
	{
		mPhasor -= 1.0f; 
		float quantizationSteps = getSteps();
		return int(inSample * quantizationSteps) / quantizationSteps;
	}
	return 0.0f;
}

void BitCrusher::Reset()
{
	mPhasor = 0.0f;
}

float BitCrusher::getSteps()
{
	return mQuantizationSteps;
}

void BitCrusher::setBits(int bitDepth)
{
	mBits = bitDepth;
	mQuantizationSteps = 1 << bitDepth;
}

float BitCrusher::getDecimation()
{
	return mDecimation;
}

void BitCrusher::setDecimation(float SampleRateDivider)
{
	mDecimation = SampleRateDivider;
}
