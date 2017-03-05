#pragma once

#include "../../../sL_Libs/iDspInterface.hpp"

struct NoiseParams : DspParams
{
	float amp;
};

class Noise : public iDspInterface<NoiseParams>
{
public:
	Noise();
	~Noise() { }

	void ProcessAudioBuffer(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	void ProcessAudioChannel(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	inline float ProcessAudioSample(float inSample, NoiseParams* params, unsigned int channel = 0) override;
	inline float ProcessAudioSample(float inSample, void* params, unsigned int channel = 0) override;

	void Release() override { };
	void Reset() override;

	float getAmp();
	void  setAmp(float);

private:
	float mCurrentAmp;
	float mTargetAmp;
	int   mInterpolationSamples;

	NoiseParams params;
};
