#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "..\..\..\FMOD_Lib\fmod.hpp"

#include "..\Gain\Gain.hpp"
//#include "..\Noise\Noise.hpp"
//#include "..\Distortion\Distortion.hpp"
//#include "..\BitCrusher\BitCrusher.hpp"

#define PLUGIN_NAME "sL Cruncher"
#define PLUGIN_VERSION 0x00010000

//extern "C"
//{
//	F_EXPORT FMOD_DSP_DESCRIPTION* F_CALL FMODGetDSPDescription();
//}
//
//FMOD_RESULT F_CALLBACK CreateCallback(FMOD_DSP_STATE *dsp);
//FMOD_RESULT F_CALLBACK ReleaseCallback(FMOD_DSP_STATE *dsp_state);
//FMOD_RESULT F_CALLBACK ShouldIProcessCallback(FMOD_DSP_STATE *dsp, FMOD_BOOL inputsidle, unsigned int length, FMOD_CHANNELMASK inmask, int inchannels, FMOD_SPEAKERMODE speakermode);
//FMOD_RESULT F_CALLBACK ReadCallback(FMOD_DSP_STATE *dsp, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int *outchannels);
//FMOD_RESULT F_CALLBACK ResetCallback(FMOD_DSP_STATE *dsp);
//FMOD_RESULT F_CALLBACK SetParameterFloat(FMOD_DSP_STATE *dsp, int index, float value);
//FMOD_RESULT F_CALLBACK GetParameterFloat(FMOD_DSP_STATE *dsp, int index, float *value, char *valuestr);
////FMOD_RESULT F_CALLBACK SetParameterInt(FMOD_DSP_STATE *dsp, int index, int value);
////FMOD_RESULT F_CALLBACK GetParameterInt(FMOD_DSP_STATE *dsp, int index, int *value, char *valuestr);
//FMOD_RESULT F_CALLBACK SysRegister(FMOD_DSP_STATE *dsp_state);
//FMOD_RESULT F_CALLBACK SysDeregister(FMOD_DSP_STATE *dsp_state);
//FMOD_RESULT F_CALLBACK SysMix(FMOD_DSP_STATE *dsp_state, int stage);

// TODO: use a enum class : char
enum
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

static bool isRunning = false;
static FMOD_DSP_PARAMETER_DESC p_gain;
//static FMOD_DSP_PARAMETER_DESC p_noiseAmp;
//static FMOD_DSP_PARAMETER_DESC p_bitDepth;
//static FMOD_DSP_PARAMETER_DESC p_decimation;
//static FMOD_DSP_PARAMETER_DESC p_cutoff;
//static FMOD_DSP_PARAMETER_DESC p_resonance;
//static FMOD_DSP_PARAMETER_DESC p_distortion;
//static FMOD_DSP_PARAMETER_DESC p_bypass;

//FMOD_DSP_PARAMETER_DESC *pluginPrameters[PLUGIN_NUM_PARAMS] =
//{
//	&p_gain,
//};
//
//FMOD_DSP_DESCRIPTION pluginDescription =
//{
//	FMOD_PLUGIN_SDK_VERSION,        // unsigned int                        pluginsdkversion;   
//	PLUGIN_NAME,					// char                                name[32];           
//	PLUGIN_VERSION,				    // unsigned int                        version;            
//	1,                              // int                                 numinputbuffers;    
//	1,                              // int                                 numoutputbuffers;   
//	CreateCallback,                 // FMOD_DSP_CREATECALLBACK             create;             
//	ReleaseCallback,                // FMOD_DSP_RELEASECALLBACK            release;            
//	ResetCallback,                  // FMOD_DSP_RESETCALLBACK              reset;              
//	ReadCallback,                   // FMOD_DSP_READ_CALLBACK              read;               
//	0,					            // FMOD_DSP_PROCESS_CALLBACK           process;            
//	0,                              // FMOD_DSP_SETPOSITIONCALLBACK        setposition;        
//	PLUGIN_NUM_PARAMS,				// int								   numparameters;    
//	pluginPrameters,				// FMOD_DSP_PARAMETER_DESC           **paramdesc;          
//	SetParameterFloat,				// FMOD_DSP_SETPARAM_FLOAT_CALLBACK    setparameterfloat;  
//	0, //SetParameterInt,				// FMOD_DSP_SETPARAM_INT_CALLBACK      setparameterint;    
//	0,                              // FMOD_DSP_SETPARAM_BOOL_CALLBACK     setparameterbool;   
//	0,                              // FMOD_DSP_SETPARAM_DATA_CALLBACK     setparameterdata;   
//	GetParameterFloat,				// FMOD_DSP_GETPARAM_FLOAT_CALLBACK    getparameterfloat;  
//	0,//GetParameterInt,				// FMOD_DSP_GETPARAM_INT_CALLBACK      getparameterint;    
//	0,                              // FMOD_DSP_GETPARAM_BOOL_CALLBACK     getparameterbool;   
//	0,                              // FMOD_DSP_GETPARAM_DATA_CALLBACK     getparameterdata;   
//	ShouldIProcessCallback,         // FMOD_DSP_SHOULDIPROCESS             shouldiprocess;     
//	0,                              // void                               *userdata;
//	SysRegister,                    // FMOD_DSP_SYSTEM_REGISTER_CALLBACK   sys_register;
//	SysDeregister,                  // FMOD_DSP_SYSTEM_DEREGISTER_CALLBACK sys_deregister;
//	SysMix                          // FMOD_DSP_SYSTEM_MIX_CALLBACK        sys_mix;
//};
//
//extern "C"
//{
//	F_EXPORT FMOD_DSP_DESCRIPTION* F_CALL FMODGetDSPDescription()
//	{
//		static float gain_dB_values[] = { -80, -50, -30, -12, -6,  0  };
//		static float gain_ui_values[] = {  0,   2,   4,   7,   8,  10 };
//
//		// GAIN IN
//		FMOD_DSP_INIT_PARAMDESC_FLOAT_WITH_MAPPING(
//			p_gain, 
//			"Gain", 
//			"unit", // "dB"
//			"Gain in dB. -80 to 0. Default = 0", 
//			DFT_GAIN_PARAM, 
//			gain_dB_values,
//			gain_ui_values);
//
//		// NOISE AMP
//
//		// BIT DEPTH
//
//		// DECIMATION
//
//		// CUTOFF
//
//		// RESONANCE
//
//		// DISTORTION
//
//		// BYPASS
//
//		return &pluginDescription;
//	}
//}


class Plugin
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
		float noiseAmp;
		int   bitDepth;
		int   decimation;
		float cutoff;
		float resonance;
		float distortion;
		bool  bypass;
	};

private:
	iDspInterface<GainParams> *dspGain; // <GUI.gain>
										//iDspInterface *dspDistortion;
};

