#pragma once

#include <cmath>
#include <math.h>
#include <string.h>
#include <stdio.h>

#define dB_MIN -80.0f
#define DECIBELS_TO_LINEAR(__dbval__)  ((__dbval__ <= dB_MIN) ? 0.0f : powf(10.0f, __dbval__ / 20.0f))
#define LINEAR_TO_DECIBELS(__linval__) ((__linval__ <= 0.0f) ? dB_MIN : 20.0f * log10f((float)__linval__))
#define INTERPOLATION_SAMPLES 256

class iDspInterface
{
public:
	~iDspInterface() {};
	virtual void ApplyDsp(float *inbuffer, float *outbuffer, float *params) = 0;
	virtual void Process(float *inbuffer, float *outbuffer, unsigned int length, int channels) = 0;
	virtual void Release() = 0;
	virtual void Reset() = 0;
};

