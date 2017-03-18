#pragma once

#include "../../../sL_Libs/iDspInterface.hpp"

class Noise : public iDspInterface
{
public:
	Noise();
	~Noise();

	void Reset() override;
	void ProcessAudioBuffer(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	void ProcessAudioChannel(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	inline float ProcessAudioSample(float inSample, unsigned int channel = 0) override;

	float getAmp();
	void  setAmp(float);

private:
	float mCurrentAmp;
	float mTargetAmp;
	int   mInterpolationSamples;
};
