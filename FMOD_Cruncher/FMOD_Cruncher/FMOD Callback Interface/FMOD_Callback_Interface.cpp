#include "FMOD_Callback_Interface.hpp"


FMOD_RESULT F_CALLBACK CreateCallback(FMOD_DSP_STATE *dsp_state)
{
	Plugin *dsp = (Plugin *)FMOD_DSP_STATE_MEMALLOC(dsp_state, sizeof(Plugin), FMOD_MEMORY_NORMAL, "Plugin");
	if (!dsp)
		return FMOD_ERR_MEMORY;
	dsp_state->plugindata = dsp;
	dsp->Create();
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK ResetCallback(FMOD_DSP_STATE *dsp_state)
{
	Plugin *dsp = static_cast<Plugin*>(dsp_state->plugindata);
	dsp->Reset();
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK ReleaseCallback(FMOD_DSP_STATE *dsp_state)
{
	Plugin *dsp = static_cast<Plugin*>(dsp_state->plugindata);
	FMOD_DSP_STATE_MEMFREE(dsp_state, dsp, FMOD_MEMORY_NORMAL, "Plugin");
	return FMOD_OK;
}

/* TODO: replace ShouldIProcessCallback and ReadCallback
*	with FMOD_DSP_PROCESS_CALLBACK to save CPU and introduce
*	plugin bypass button.
*/
/*==========================================================================================================================================================*/

FMOD_RESULT F_CALLBACK ShouldIProcessCallback(FMOD_DSP_STATE * /*dsp_state*/, FMOD_BOOL inputsidle, unsigned int /*length*/, FMOD_CHANNELMASK /*inmask*/, int /*inchannels*/, FMOD_SPEAKERMODE /*speakermode*/)
{
	//Plugin *dsp = static_cast<Plugin*>(dsp_state->plugindata);
	if (inputsidle)
		return FMOD_ERR_DSP_DONTPROCESS;
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK ReadCallback(FMOD_DSP_STATE *dsp_state, float *inBuffer, float *outBuffer, unsigned int length, int inchannels, int *outchannels)
{
	Plugin *dsp = static_cast<Plugin*>(dsp_state->plugindata);
	dsp->Process(inBuffer, outBuffer, length, inchannels);
	return FMOD_OK;
}

/*==========================================================================================================================================================*/

FMOD_RESULT F_CALLBACK SetParameterFloat(FMOD_DSP_STATE *dsp_state, int index, float value)
{
	Plugin *dsp = static_cast<Plugin*>(dsp_state->plugindata);
	dsp->setParameterFloat(index, value);
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK GetParameterFloat(FMOD_DSP_STATE *dsp_state, int index, float *value, char *valuestr)
{
	Plugin *dsp = static_cast<Plugin*>(dsp_state->plugindata);
	dsp->getParameterFloat(index, value, valuestr);
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK SetParameterInt(FMOD_DSP_STATE *dsp_state, int index, int value)
{
	Plugin *dsp = static_cast<Plugin*>(dsp_state->plugindata);
	dsp->setParameterInt(index, value);
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK GetParameterInt(FMOD_DSP_STATE *dsp_state, int index, int *value, char *valuestr)
{
	Plugin *dsp = static_cast<Plugin*>(dsp_state->plugindata);
	dsp->getParameterInt(index, value, valuestr);
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK SysRegister(FMOD_DSP_STATE * /*dsp_state*/)
{
	// called once for this type of dsp being loaded or registered (it is not per instance)
	isRunning = true;
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK SysDeregister(FMOD_DSP_STATE * /*dsp_state*/)
{
	// called once for this type of dsp being unloaded or de-registered (it is not per instance)
	isRunning = false;
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK SysMix(FMOD_DSP_STATE * /*dsp_state*/, int /*stage*/)
{
	// stage == 0 , before all dsps are processed/mixed, this callback is called once for this type.
	// stage == 1 , after all dsps are processed/mixed, this callback is called once for this type.
	return FMOD_OK;
}