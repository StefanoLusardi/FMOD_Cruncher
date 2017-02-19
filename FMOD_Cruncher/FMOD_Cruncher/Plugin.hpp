#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "../../FMOD_PLUGINS_LIB/fmod.hpp"
#include "iDspInterface.hpp"
#include "iPluginInterface.hpp"
#include "Distortion.hpp"
#include "Gain.hpp"

#define PLUGIN_NAME "sL Plugin"
#define PLUGIN_VERSION 0x00010000

extern "C"
{
	F_EXPORT FMOD_DSP_DESCRIPTION* F_CALL FMODGetDSPDescription();
}

FMOD_RESULT F_CALLBACK createCallback(FMOD_DSP_STATE *dsp);
FMOD_RESULT F_CALLBACK releaseCallback(FMOD_DSP_STATE *dsp_state);
FMOD_RESULT F_CALLBACK shouldIProcessCallback(FMOD_DSP_STATE *dsp, FMOD_BOOL inputsidle, unsigned int length, FMOD_CHANNELMASK inmask, int inchannels, FMOD_SPEAKERMODE speakermode);
FMOD_RESULT F_CALLBACK readCallback(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int *outchannels);
FMOD_RESULT F_CALLBACK resetCallback(FMOD_DSP_STATE *dsp);
FMOD_RESULT F_CALLBACK setParameterFloat(FMOD_DSP_STATE *dsp, int index, float value);
FMOD_RESULT F_CALLBACK getParameterFloat(FMOD_DSP_STATE *dsp, int index, float *value, char *valuestr);
//FMOD_RESULT F_CALLBACK setParameterInt(FMOD_DSP_STATE *dsp, int index, int value);
//FMOD_RESULT F_CALLBACK getParameterInt(FMOD_DSP_STATE *dsp, int index, int *value, char *valuestr);
FMOD_RESULT F_CALLBACK sysRegister(FMOD_DSP_STATE *dsp_state);
FMOD_RESULT F_CALLBACK sysDeregister(FMOD_DSP_STATE *dsp_state);
FMOD_RESULT F_CALLBACK sysMix(FMOD_DSP_STATE *dsp_state, int stage);

enum
{
	UI_PARAM_GAIN = 0,
	//UI_PARAM_DISTORTION,
	PLUGIN_NUM_PARAMS
};

const float MIN_GAIN_PARAM = -80.0f;
const float MAX_GAIN_PARAM = 12.0f;
const float DFT_GAIN_PARAM = 0.0f;

static bool isRunning = false;
static FMOD_DSP_PARAMETER_DESC p_gain;

FMOD_DSP_PARAMETER_DESC *pluginPrameters[PLUGIN_NUM_PARAMS] =
{
	&p_gain,
};

FMOD_DSP_DESCRIPTION pluginDescription =
{
	FMOD_PLUGIN_SDK_VERSION,        // unsigned int                        pluginsdkversion;   
	PLUGIN_NAME,					// char                                name[32];           
	PLUGIN_VERSION,				    // unsigned int                        version;            
	1,                              // int                                 numinputbuffers;    
	1,                              // int                                 numoutputbuffers;   
	createCallback,                 // FMOD_DSP_CREATECALLBACK             create;             
	releaseCallback,                // FMOD_DSP_RELEASECALLBACK            release;            
	resetCallback,                  // FMOD_DSP_RESETCALLBACK              reset;              
	readCallback,                   // FMOD_DSP_READ_CALLBACK              read;               
	0,					            // FMOD_DSP_PROCESS_CALLBACK           process;            
	0,                              // FMOD_DSP_SETPOSITIONCALLBACK        setposition;        
	PLUGIN_NUM_PARAMS,				// int								   numparameters;    
	pluginPrameters,				// FMOD_DSP_PARAMETER_DESC           **paramdesc;          
	setParameterFloat,				// FMOD_DSP_SETPARAM_FLOAT_CALLBACK    setparameterfloat;  
	0, //setParameterInt,				// FMOD_DSP_SETPARAM_INT_CALLBACK      setparameterint;    
	0,                              // FMOD_DSP_SETPARAM_BOOL_CALLBACK     setparameterbool;   
	0,                              // FMOD_DSP_SETPARAM_DATA_CALLBACK     setparameterdata;   
	getParameterFloat,				// FMOD_DSP_GETPARAM_FLOAT_CALLBACK    getparameterfloat;  
	0, //getParameterInt,				// FMOD_DSP_GETPARAM_INT_CALLBACK      getparameterint;    
	0,                              // FMOD_DSP_GETPARAM_BOOL_CALLBACK     getparameterbool;   
	0,                              // FMOD_DSP_GETPARAM_DATA_CALLBACK     getparameterdata;   
	shouldIProcessCallback,         // FMOD_DSP_SHOULDIPROCESS             shouldiprocess;     
	0,                              // void                               *userdata;
	sysRegister,                    // FMOD_DSP_SYSTEM_REGISTER_CALLBACK   sys_register;
	sysDeregister,                  // FMOD_DSP_SYSTEM_DEREGISTER_CALLBACK sys_deregister;
	sysMix                          // FMOD_DSP_SYSTEM_MIX_CALLBACK        sys_mix;
};

extern "C"
{
	F_EXPORT FMOD_DSP_DESCRIPTION* F_CALL FMODGetDSPDescription()
	{
		static float gain_mapping_values[] = { -80, -50, -30, -10, 0, 10 };
		static float gain_mapping_scale[] = { 0, 2, 4, 7, 8, 10 };

		FMOD_DSP_INIT_PARAMDESC_FLOAT_WITH_MAPPING(p_gain, "Gain", "unit", "Gain in dB. -80 to 10. Default = 0", DFT_GAIN_PARAM, gain_mapping_values, gain_mapping_scale);
		return &pluginDescription;
	}
}

class Plugin //: public iPluginInterface
{
public:
	Plugin() {};

	void Create();
	void Release();
	void Process(float *inbuffer, float *outbuffer, unsigned int length, int channels);
	void Reset();

	void setParameterFloat(int index, float value);
	void getParameterFloat(int index, float *value, char *valuestr);
	//void setParameterInt(int index, int value);
	//void getParameterInt(int index, int *value, char *valuestr);
	//void setParameterBool(int index, bool value);
	//void getParameterBool(int index, bool *value, char *valuestr);
	//void setParameterData(int index, int value);
	//void getParameterData(int index, int *value, char *valuestr);

	struct GUI
	{
		float gain;
		//float distortion;
	};

private:
	iDspInterface *dspGain;
	//iDspInterface *dspDistortion;
};

