#pragma once

#include "../../../sL_Libs/iDspInterface.hpp"

struct DistortionParams : iDspParams
{
	float level;
};

class Distortion : public iDspInterface
{
public:
	Distortion();
	~Distortion();

	void ProcessAudioBuffer(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	void ProcessAudioChannel(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	inline float ProcessAudioSample(float inSample, iDspParams* params, unsigned int channel = 0) override;

	void Release() override { };
	void Reset() override;

	float getLevel();
	void  setLevel(float);

private:
	float mCurrentLevel;
	float mTargetLevel;
	int   mInterpolationSamples;

	DistortionParams* params;
};