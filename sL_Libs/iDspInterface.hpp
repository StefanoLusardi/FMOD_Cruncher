#pragma once

#include <cmath>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define dB_MIN -80.0f
#define INTERPOLATION_SAMPLES 256

// TODO: create inline functions instead of macros
#define DECIBELS_TO_LINEAR(__dbval__)  ((__dbval__ <= dB_MIN) ? 0.0f : powf(10.0f, __dbval__ / 20.0f))
#define LINEAR_TO_DECIBELS(__linval__) ((__linval__ <= 0.0f) ? dB_MIN : 20.0f * log10f((float)__linval__))


const float MIN_GAIN_PARAM = -80.0f;
const float MAX_GAIN_PARAM = 0.0f;
const float DFT_GAIN_PARAM = 0.0f;

template <typename P>
class iDspInterface
{
public:
	virtual ~iDspInterface() = 0 { };
	virtual inline void ApplyDsp(float inSample, float outSample, P* params) = 0;
	virtual inline void ApplyDsp(float inSample, float outSample, void* params) = 0;
	virtual void Process(float *inbuffer, float *outbuffer, unsigned int length, int channels) = 0;
	virtual void Release() = 0;
	virtual void Reset() = 0;
};

class DspParams
{
public:
	virtual ~DspParams() = 0 { };
};