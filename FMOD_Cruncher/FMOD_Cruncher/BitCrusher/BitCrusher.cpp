#include "BitCrusher.hpp"

BitCrusher::BitCrusher()
{
	params = new BitCrusherParams();
	BitCrusher::Reset();
}

BitCrusher::~BitCrusher()
{
	delete params;
}

void BitCrusher::ProcessAudioBuffer(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	unsigned int samples = length * channels;
	params->bitDepth = mBits;
	params->decimationRate = mDecimation;
	while (samples--)
	{
		*outBuffer++ = ProcessAudioSample(*inBuffer++, params);
	}
}

/* NOT USED */
void BitCrusher::ProcessAudioChannel(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (unsigned int ch = 0; ch < static_cast<unsigned int>(channels); ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, params, ch);
		}
	}
}

inline float BitCrusher::ProcessAudioSample(float inSample, iDspParams * params, unsigned int channel)
{
	float rate = 1 / float(static_cast<BitCrusherParams*>(params)->decimationRate);
	mPhasor += rate;

	if (mPhasor >= 1.0f)
	{
		mPhasor -= 1.0f; 
		int bits = static_cast<BitCrusherParams*>(params)->bitDepth;
		double step = 1 << bits;
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

int BitCrusher::getDecimation()
{
	return mDecimation;
}

void BitCrusher::setDecimation(int SampleRateDivider)
{
	mDecimation = SampleRateDivider;
}
