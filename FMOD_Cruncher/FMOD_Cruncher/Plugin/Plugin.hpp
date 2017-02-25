#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "..\..\..\FMOD_Lib\fmod.hpp"
//#include "..\Plugin\PluginUI.hpp"
#include "..\Gain\Gain.hpp"
#include "..\Noise\Noise.hpp"
#include "..\Distortion\Distortion.hpp"
#include "..\BitCrusher\BitCrusher.hpp"

#define PLUGIN_NAME "sL Cruncher"
#define PLUGIN_VERSION 0x00010000

// TODO: move this into PluginUI.hpp
enum class UiParams : int
{
	UI_PARAM_GAIN = 0,
	//UI_PARAM_NOISE_AMP
	//UI_PARAM_BIT_DEPTH
	//UI_PARAM_DECIMATION
	//UI_PARAM_CUTOFF
	//UI_PARAM_RESONANCE
	//UI_PARAM_DISTORTION
	//UI_PARAM_BYPASS
	PLUGIN_NUM_PARAMS
};

// TODO: move this into PluginUI.hpp
static bool isRunning = false;
static FMOD_DSP_PARAMETER_DESC p_gain;
//static FMOD_DSP_PARAMETER_DESC p_noiseAmp;
//static FMOD_DSP_PARAMETER_DESC p_bitDepth;
//static FMOD_DSP_PARAMETER_DESC p_decimation;
//static FMOD_DSP_PARAMETER_DESC p_cutoff;
//static FMOD_DSP_PARAMETER_DESC p_resonance;
//static FMOD_DSP_PARAMETER_DESC p_distortion;
//static FMOD_DSP_PARAMETER_DESC p_bypass;

class Plugin
{
public:
	Plugin() {};

	void Create();
	void Release();
	void Process(float *inBuffer, float *outBuffer, unsigned int length, int channels);
	void Reset();

	void setParameterFloat(int index, float value);
	void getParameterFloat(int index, float *value, char *valuestr);
	//void setParameterInt(int index, int value);
	//void getParameterInt(int index, int *value, char *valuestr);
	//void setParameterBool(int index, bool value);
	//void getParameterBool(int index, bool *value, char *valuestr);

private:
	iDspInterface<GainParams> *dspGain;
};

