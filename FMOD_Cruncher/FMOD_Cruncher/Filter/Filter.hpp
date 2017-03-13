#pragma once
#include "../../../sL_Libs/iDspInterface.hpp"

#define DSP_MAX_CHANNELS 2
#define FILTER_ORDER 2

typedef struct
{
	float a0, a1, a2; 
	float b0, b1, b2; 
} Biquad;

class Filter : public iDspInterface
{
public:
	Filter();
	~Filter();

	void ProcessAudioBuffer(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	void ProcessAudioChannel(float *inBuffer, float *outBuffer, unsigned int length, int channels) override;
	inline float ProcessAudioSample(float inSample, unsigned int channel = 0) override;

	void Release() override { };
	void Reset() override;
	
	void szTransform(float *a0, float *a1, float *a2, float *b0, float *b1, float *b2, float fc, float fs, float *k, float *coef);
	void Prewarp(float *a0, float *a1, float *a2, float fc, float fs); 
	void Bilinear(float a0, float a1, float a2, float b0, float b1, float b2, float *k, float fs, float *coef);
	void UpdateState(float resonance, float cutoff);

	float getCutoff();
	void  setCutoff(float);

	float getResonance();
	void  setResonance(float);

private:
	float  mGainFactor[FILTER_ORDER];
	float  mHistory[DSP_MAX_CHANNELS][2 * FILTER_ORDER];
	float  mCoefficients[4 * FILTER_ORDER + 1];         
	Biquad mProtoCoef[FILTER_ORDER];

	float mCurrentCutoff;
	float mTargetCutoff;
	float mCurrentResonance;
	float mTargetResonance;
	int   mInterpolationSamples;
};

