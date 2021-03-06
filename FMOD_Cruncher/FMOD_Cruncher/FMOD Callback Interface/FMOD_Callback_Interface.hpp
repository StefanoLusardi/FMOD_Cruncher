#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "../Plugin/Plugin.hpp"

extern "C"
{
	F_EXPORT FMOD_DSP_DESCRIPTION* F_CALL FMODGetDSPDescription();
}

FMOD_RESULT F_CALLBACK CreateCallback(FMOD_DSP_STATE *dsp);
FMOD_RESULT F_CALLBACK ReleaseCallback(FMOD_DSP_STATE *dsp_state);
//FMOD_RESULT F_CALLBACK ShouldIProcessCallback(FMOD_DSP_STATE *dsp, FMOD_BOOL inputsidle, unsigned int length, FMOD_CHANNELMASK inmask, int channels, FMOD_SPEAKERMODE speakermode);
//FMOD_RESULT F_CALLBACK ReadCallback(FMOD_DSP_STATE *dsp, float *inBuffer, float *outBuffer, unsigned int length, int channels, int *outchannels);
FMOD_RESULT F_CALLBACK ProcessCallback(FMOD_DSP_STATE *dsp_state, unsigned int length, const FMOD_DSP_BUFFER_ARRAY *inbufferarray, FMOD_DSP_BUFFER_ARRAY *outbufferarray, FMOD_BOOL inputsidle, FMOD_DSP_PROCESS_OPERATION op);
FMOD_RESULT F_CALLBACK ResetCallback(FMOD_DSP_STATE *dsp);
FMOD_RESULT F_CALLBACK SetParameterFloat(FMOD_DSP_STATE *dsp, int index, float value);
FMOD_RESULT F_CALLBACK GetParameterFloat(FMOD_DSP_STATE *dsp, int index, float *value, char *valuestr);
FMOD_RESULT F_CALLBACK SetParameterInt(FMOD_DSP_STATE *dsp, int index, int value);
FMOD_RESULT F_CALLBACK GetParameterInt(FMOD_DSP_STATE *dsp, int index, int *value, char *valuestr);
//FMOD_RESULT F_CALLBACK SetParameterBool(FMOD_DSP_STATE *dsp, int index, bool value); //FMOD_BOOL
//FMOD_RESULT F_CALLBACK GetParameterBool(FMOD_DSP_STATE *dsp, int index, bool *value, char *valuestr); //FMOD_BOOL
FMOD_RESULT F_CALLBACK SysRegister(FMOD_DSP_STATE *dsp_state);
FMOD_RESULT F_CALLBACK SysDeregister(FMOD_DSP_STATE *dsp_state);
FMOD_RESULT F_CALLBACK SysMix(FMOD_DSP_STATE *dsp_state, int stage);

FMOD_DSP_DESCRIPTION pluginDescription =
{
	FMOD_PLUGIN_SDK_VERSION, // unsigned int                        pluginsdkversion;   
	PLUGIN_NAME,			 // char                                name[32];           
	PLUGIN_VERSION,			 // unsigned int                        version;            
	1,                       // int                                 numinputbuffers;    
	1,                       // int                                 numoutputbuffers;   
	CreateCallback,          // FMOD_DSP_CREATECALLBACK             create;             
	ReleaseCallback,         // FMOD_DSP_RELEASECALLBACK            release;            
	ResetCallback,           // FMOD_DSP_RESETCALLBACK              reset;              
	0,//ReadCallback,            // FMOD_DSP_READ_CALLBACK              read;               
	ProcessCallback,					     // FMOD_DSP_PROCESS_CALLBACK           process;            
	0,                       // FMOD_DSP_SETPOSITIONCALLBACK        setposition;        
	static_cast<int>(UiParams::PLUGIN_NUM_PARAMS),	// int								   numparameters;    
	pluginPrameters,		 // FMOD_DSP_PARAMETER_DESC           **paramdesc;          
	SetParameterFloat,		 // FMOD_DSP_SETPARAM_FLOAT_CALLBACK    setparameterfloat;  
	SetParameterInt,		 // FMOD_DSP_SETPARAM_INT_CALLBACK      setparameterint;    
	0,//SetParameterBool,    // FMOD_DSP_SETPARAM_BOOL_CALLBACK     setparameterbool;   
	0,                       // FMOD_DSP_SETPARAM_DATA_CALLBACK     setparameterdata;   
	GetParameterFloat,		 // FMOD_DSP_GETPARAM_FLOAT_CALLBACK    getparameterfloat;  
	GetParameterInt,		 // FMOD_DSP_GETPARAM_INT_CALLBACK      getparameterint;    
	0,//GetParameterBool,    // FMOD_DSP_GETPARAM_BOOL_CALLBACK     getparameterbool;   
	0,                       // FMOD_DSP_GETPARAM_DATA_CALLBACK     getparameterdata;   
	0,//ShouldIProcessCallback,  // FMOD_DSP_SHOULDIPROCESS             shouldiprocess;     
	0,                       // void                               *userdata;
	SysRegister,             // FMOD_DSP_SYSTEM_REGISTER_CALLBACK   sys_register;
	SysDeregister,           // FMOD_DSP_SYSTEM_DEREGISTER_CALLBACK sys_deregister;
	SysMix                   // FMOD_DSP_SYSTEM_MIX_CALLBACK        sys_mix;
};

extern "C"
{
	F_EXPORT FMOD_DSP_DESCRIPTION* F_CALL FMODGetDSPDescription()
	{
		static float gain_dB_values[] = { -80, -50, -30, -6,  0,  6 };
		static float gain_ui_values[] = {  0,   2,   4,   6,  8,  10 };

		// GAIN IN
		FMOD_DSP_INIT_PARAMDESC_FLOAT_WITH_MAPPING(
			p_gain,
			"GainIn",
			"dB",
			"Gain in dB. -80 to +6. Default = 0",
			MathLib::ZeroGain_dB,
			gain_dB_values,
			gain_ui_values);

		// NOISE AMP
		FMOD_DSP_INIT_PARAMDESC_FLOAT_WITH_MAPPING(
			p_noiseAmp,
			"Noise",
			"dB",
			"Noise Level in dB. -80 to 0. Default = -80",
			MathLib::MinGain_dB,
			gain_dB_values,
			gain_ui_values);

		// BIT DEPTH
		FMOD_DSP_INIT_PARAMDESC_INT(
			p_bitDepth,
			"BitDepth",
			"",
			"Bith Depth. 16 to 1. Default = 16",
			1, 
			16, 
			16, 
			false,
			nullptr);

		// DECIMATION
		FMOD_DSP_INIT_PARAMDESC_FLOAT(
			p_decimation,
			"Decimation",
			"",
			"Sample Rate Divider. 1 to 50. Default = 1",
			0.01f,
			1.0f,
			1.0f,
			true);

		// CUTOFF
		FMOD_DSP_INIT_PARAMDESC_FLOAT(
			p_cutoff,
			"Cutoff",
			"hz",
			"Lowpass cutoff frequency in hz.   1.0 to output 22000.0.  Default = 5000.0.",
			10.0f,
			22000.0f,
			22000.0f,
			false);

		// RESONANCE
		FMOD_DSP_INIT_PARAMDESC_FLOAT(
			p_resonance,
			"Resonance",
			"",
			"Lowpass resonance Q value. 1.0 to 10.0.  Default = 1.0.",
			1.0f,
			10.0f,
			1.0f,
			false);

		// DISTORTION
		FMOD_DSP_INIT_PARAMDESC_FLOAT(
			p_distortion,
			"Distortion",
			"",
			"Distortion Level. 0 to 1. Default = 0",
			0.05f, // Min
			1.0f, // Max
			0.0f, // Default
			true);

		// BYPASS
		FMOD_DSP_INIT_PARAMDESC_FLOAT(
			p_bypass,
			"Bypass",
			"",
			"Plugin Bypass. True or False. Default = false",
			0.0f, // Min
			1.0f, // Max
			0.0f, // Default
			false);

		return &pluginDescription;
	}
}