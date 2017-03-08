#pragma once

#include "../../../sL_Libs/iDspInterface.hpp"

struct BitCrusherParams : iDspParams
{
	int bitDepth;
	float decimationRate;
};

class BitCrusher : public iDspInterface
{
public:
	BitCrusher();
	~BitCrusher();

	void ProcessAudioBuffer(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	void ProcessAudioChannel(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	inline float ProcessAudioSample(float inSample, iDspParams* params, unsigned int channel = 0) override;

	void Release() override { };
	void Reset() override;

	int  getBits();
	void setBits(int);

	float  getDecimation();
	void setDecimation(float);

private:
	int mBits;		// Bit depth: [15..1] 
	float mDecimation;	// Sample rate divider: [1..0.01]
	float mPhasor;
	int   mInterpolationSamples;

	BitCrusherParams* params;
};