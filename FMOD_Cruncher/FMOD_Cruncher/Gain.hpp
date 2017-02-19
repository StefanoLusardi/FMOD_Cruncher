#pragma once

#include "iDspInterface.hpp"

class Gain : public iDspInterface
{
public:
	Gain();
	~Gain() {};
	inline void ApplyDsp(float inSample, float outSample, float *gain);
	void Process(float *inbuffer, float *outbuffer, unsigned int length, int channels);
	void Reset();
	void Release() {};

	float getAmount();
	void  setAmount(float gain);


private:
	float mCurrentGain;
	float mTargetGain;
	int mInterpolationSamples;
};


