#pragma once

#include "../../../sL_Libs/iDspInterface.hpp"

struct GainParams : DspParams
{
	float gain;
};

class Gain : public iDspInterface<GainParams>
{
public:
	Gain();
	~Gain() {};

	void ProcessAudioBuffer(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	void ProcessAudioChannel(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	inline float ProcessAudioSample(float inSample, GainParams* params, unsigned int channel = 0) override;
	inline float ProcessAudioSample(float inSample, void* params, unsigned int channel = 0) override;

	void Release() override {};
	void Reset() override;

	float getGain();
	void  setGain(float gain);

private:
	float mCurrentGain;
	float mTargetAmp;
	int   mInterpolationSamples;

	GainParams params;
};
