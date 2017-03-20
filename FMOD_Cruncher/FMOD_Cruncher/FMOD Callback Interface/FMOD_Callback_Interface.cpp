#include "FMOD_Callback_Interface.hpp"


FMOD_RESULT F_CALLBACK CreateCallback(FMOD_DSP_STATE *dsp_state)
{
	Plugin *dsp = (Plugin*)FMOD_DSP_STATE_MEMALLOC(dsp_state, sizeof(Plugin), FMOD_MEMORY_NORMAL, "Plugin");
	if (!dsp) 
		return FMOD_ERR_MEMORY;
	dsp_state->plugindata = dsp;
	dsp->Create(dsp_state);
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

FMOD_RESULT F_CALLBACK ProcessCallback(FMOD_DSP_STATE *dsp_state, unsigned int length, const FMOD_DSP_BUFFER_ARRAY *inbufferarray, FMOD_DSP_BUFFER_ARRAY *outbufferarray, FMOD_BOOL /*inputsidle*/, FMOD_DSP_PROCESS_OPERATION op)
{
	Plugin *dsp = static_cast<Plugin*>(dsp_state->plugindata);
	if (op == FMOD_DSP_PROCESS_QUERY)
	{
		if (outbufferarray && inbufferarray)
		{
			outbufferarray[0].bufferchannelmask[0] = inbufferarray[0].bufferchannelmask[0];
			outbufferarray[0].buffernumchannels[0] = inbufferarray[0].buffernumchannels[0];
			outbufferarray[0].speakermode = inbufferarray[0].speakermode;
		}
	}
	else
	{
		// Check if bypass is active before processing audio data.
		if (dsp->getBypass())
		{
			dsp->Bypass(inbufferarray[0].buffers[0], outbufferarray[0].buffers[0], length, inbufferarray[0].buffernumchannels[0]);
			return FMOD_OK;
		}
		// Process audio data.
		dsp->Process(inbufferarray[0].buffers[0], outbufferarray[0].buffers[0], length, inbufferarray[0].buffernumchannels[0]); // input and output channels count match for this effect
		return FMOD_OK;		
	}
	return FMOD_OK;
}

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