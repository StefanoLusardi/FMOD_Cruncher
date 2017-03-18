#pragma once

#include "../../../sL_Libs/iDspInterface.hpp"

class Gain : public iDspInterface
{
public:
	Gain();
	~Gain();

	void Reset() override;
	void ProcessAudioBuffer(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	void ProcessAudioChannel(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	inline float ProcessAudioSample(float inSample, unsigned int channel = 0) override;

	float getGain();
	void  setGain(float);

private:
	float mCurrentGain;
	float mTargetGain;
	int   mInterpolationSamples;
};
