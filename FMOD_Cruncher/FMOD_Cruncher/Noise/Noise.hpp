#pragma once

#include "../../../sL_Libs/iDspInterface.hpp"

struct NoiseParams : iDspParams
{
	float amp;
};

class Noise : public iDspInterface
{
public:
	Noise();
	~Noise();

	void ProcessAudioBuffer(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	void ProcessAudioChannel(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	inline float ProcessAudioSample(float inSample, iDspParams* params, unsigned int channel = 0) override;
	
	void Release() override { };
	void Reset() override;

	float getAmp();
	void  setAmp(float);

private:
	float mCurrentAmp;
	float mTargetAmp;
	int   mInterpolationSamples;

	NoiseParams* params;
};
