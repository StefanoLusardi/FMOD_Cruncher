#pragma once
#include "../../../sL_Libs/iDspInterface.hpp"

struct FilterParams : iDspParams
{
	float cutoff;
	float resonance;
};

class Filter : public iDspInterface
{
public:
	Filter();
	~Filter();

	void ProcessAudioBuffer(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	void ProcessAudioChannel(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	inline float ProcessAudioSample(float inSample, iDspParams* params, unsigned int channel = 0) override;

	void Release() override { };
	void Reset() override;

	float getCutoff();
	void  setCutoff(float);

	float getResonance();
	void  setResonance(float);

private:
	float mCurrentCutoff;
	float mTargetCutoff;
	float mCurrentResonance;
	float mTargetResonance;
	int   mInterpolationSamples;

	FilterParams* params;
};

