#pragma once

#include "iDspInterface.hpp"

struct GainParams : DspParams
{
	float gain;
};

class Gain : public iDspInterface<GainParams>
{
public:
	Gain();
	~Gain() {};

	inline void ApplyDsp(float inSample, float outSample, GainParams* params) override;
	void Process(float *inbuffer, float *outbuffer, unsigned int length, int channels) override;
	void Reset() override;
	void Release() override {};

	float getAmount();
	void  setAmount(float gain);


private:
	float mCurrentGain;
	float mTargetGain;
	int   mInterpolationSamples;

	GainParams params;
};
