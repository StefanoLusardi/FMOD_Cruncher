#pragma once

#include "MathLib.h"
#include <vector>

class iDspInterface
{
public:
	virtual ~iDspInterface() = 0 { };

	virtual void Reset() = 0;
	virtual void ProcessAudioBuffer(float *inbuffer, float *outbuffer, unsigned int length, int channels) = 0;
	virtual void ProcessAudioChannel(float *inbuffer, float *outbuffer, unsigned int length, int channels) = 0;
	virtual inline float ProcessAudioSample(float inSample, unsigned int channel) = 0;
};

