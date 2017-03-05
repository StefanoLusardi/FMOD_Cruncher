#pragma once

#include "MathLib.hpp"

template <typename PARAMS>
class iDspInterface
{
public:
	virtual ~iDspInterface() = 0 { };
	virtual void ProcessAudioBuffer(float *inbuffer, float *outbuffer, unsigned int length, int channels) = 0;
	virtual void ProcessAudioChannel(float *inbuffer, float *outbuffer, unsigned int length, int channels) = 0;
	virtual inline float ProcessAudioSample(float inSample, PARAMS* params, unsigned int channel) = 0;
	virtual inline float ProcessAudioSample(float inSample, void* params, unsigned int channel) = 0;
	virtual void Release() = 0;
	virtual void Reset() = 0;
};

class DspParams
{
public:
	virtual ~DspParams() = 0 { };
};