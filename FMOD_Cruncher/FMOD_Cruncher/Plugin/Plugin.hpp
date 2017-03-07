#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "../../../FMOD_Lib/fmod.hpp"
#include "../Plugin/PluginParams.hpp"
#include "../Gain/Gain.hpp"
#include "../Noise/Noise.hpp"
#include "../Distortion/Distortion.hpp"
#include "../BitCrusher/BitCrusher.hpp"

// TODO: Plugin Interface implementation??
class Plugin // : iPluginInterface
{
public:
	Plugin() :	dspGain(nullptr), 
				dspNoise(nullptr), 
				dspDistortion(nullptr),
				dspBitCrush(nullptr)
	{ }

	void Create();
	void Release();
	void Process(float *inBuffer, float *outBuffer, unsigned int length, int channels);
	void Reset();

	void setParameterFloat(int index, float value);
	void getParameterFloat(int index, float *value, char *valuestr);
	void setParameterInt(int index, int value);
	void getParameterInt(int index, int *value, char *valuestr);
	//void setParameterBool(int index, bool value);
	//void getParameterBool(int index, bool *value, char *valuestr);

private:
	iDspInterface* dspGain;
	iDspInterface* dspNoise;
	iDspInterface* dspDistortion;
	iDspInterface* dspBitCrush;
};

