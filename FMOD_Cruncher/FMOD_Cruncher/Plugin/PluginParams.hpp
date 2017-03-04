#pragma once

#define PLUGIN_NAME "sL Cruncher"
#define PLUGIN_VERSION 0x00010000

enum class UiParams : int
{
	UI_PARAM_GAIN = 0,
	UI_PARAM_NOISE_AMP,
	UI_PARAM_BIT_DEPTH,
	UI_PARAM_DECIMATION,
	UI_PARAM_CUTOFF,
	UI_PARAM_RESONANCE,
	UI_PARAM_DISTORTION,
	UI_PARAM_BYPASS,
	PLUGIN_NUM_PARAMS
};

static bool isRunning = false;
static FMOD_DSP_PARAMETER_DESC p_gain;
static FMOD_DSP_PARAMETER_DESC p_noiseAmp;
static FMOD_DSP_PARAMETER_DESC p_bitDepth;
static FMOD_DSP_PARAMETER_DESC p_decimation;
static FMOD_DSP_PARAMETER_DESC p_cutoff;
static FMOD_DSP_PARAMETER_DESC p_resonance;
static FMOD_DSP_PARAMETER_DESC p_distortion;
static FMOD_DSP_PARAMETER_DESC p_bypass;

static FMOD_DSP_PARAMETER_DESC *pluginPrameters[static_cast<int>(UiParams::PLUGIN_NUM_PARAMS)] =
{
	&p_gain,
	&p_noiseAmp,
	&p_bitDepth,
	&p_decimation,
	&p_cutoff,
	&p_resonance,
	&p_distortion,
	&p_bypass
};