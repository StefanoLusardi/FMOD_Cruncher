#include "BitCrusher.hpp"

BitCrusher::BitCrusher()
{
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
		for (unsigned int ch = 0; ch < static_cast<unsigned int>(channels); ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, ch);
		}
	}
}

inline float BitCrusher::ProcessAudioSample(float inSample, unsigned int channel)
{
	float rate = getDecimation();
	mPhasor += rate;

	if (mPhasor >= 1.0f)
	{
		mPhasor -= 1.0f; 
		int bits = getBits();
		float step = 1 << bits;
		return int(inSample * step) / step;
	}
	return 0.0f;
}

void BitCrusher::Reset()
{
	mBits = 15;
	mDecimation = 1;
	mPhasor = 0.0f;
}

int BitCrusher::getBits()
{
	return mBits;
}

void BitCrusher::setBits(int bitDepth)
{
	mBits = bitDepth;
	//mBits = 1 << (bitDepth - 1);
}

float BitCrusher::getDecimation()
{
	return mDecimation;
}

void BitCrusher::setDecimation(float SampleRateDivider)
{
	mDecimation = SampleRateDivider;
}
