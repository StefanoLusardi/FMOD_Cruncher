#include "Plugin.hpp"

void Plugin::Create()
{
	dspGain = new Gain();
}

void Plugin::Release()
{
	if (dspGain)
	{
		dspGain->Release();
		delete dspGain;
	}
}

void Plugin::Process(float * inbuffer, float * outbuffer, unsigned int length, int channels)
{
	dspGain->Process(inbuffer, outbuffer, length, channels);
}

void Plugin::Reset()
{
	if (dspGain)
		delete dspGain;

	dspGain = new Gain();
}

void Plugin::setParameterFloat(int index, float value)
{
	switch (index)
	{
	case UI_PARAM_GAIN:
		if (dspGain)
			((Gain *)dspGain)->setAmount(value);
		break;
	}
}

void Plugin::getParameterFloat(int index, float * value, char * valuestr)
{
	switch (index)
	{
	case UI_PARAM_GAIN:
		*value = ((Gain *)dspGain)->getAmount();
		if (valuestr) sprintf(valuestr, "%.1f dB", ((Gain *)dspGain)->getAmount());
		break;
	}
}

//void Plugin::setParameterInt(int index, int value)
//{
//}
//
//void Plugin::getParameterInt(int index, int * value, char * valuestr)
//{
//}
//
//void Plugin::setParameterBool(int index, bool value)
//{
//}
//
//void Plugin::getParameterBool(int index, bool * value, char * valuestr)
//{
//}
//
//void Plugin::setParameterData(int index, int value)
//{
//}
//
//void Plugin::getParameterData(int index, int * value, char * valuestr)
//{
//}


/*        FMOD CALLBACK INTERFACE        */

FMOD_RESULT F_CALLBACK createCallback(FMOD_DSP_STATE *dsp_state)
{
	Plugin *dsp = (Plugin *)FMOD_DSP_STATE_MEMALLOC(dsp_state, sizeof(Plugin), FMOD_MEMORY_NORMAL, "Plugin");
	if (!dsp)
		return FMOD_ERR_MEMORY;
	dsp_state->plugindata = dsp;
	dsp->Create();
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK resetCallback(FMOD_DSP_STATE *dsp_state)
{
	Plugin *dsp = (Plugin *)dsp_state->plugindata;
	dsp->Reset();
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK releaseCallback(FMOD_DSP_STATE *dsp_state)
{
	Plugin *dsp = (Plugin *)dsp_state->plugindata;
	FMOD_DSP_STATE_MEMFREE(dsp_state, dsp, FMOD_MEMORY_NORMAL, "Plugin");
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK shouldIProcessCallback(FMOD_DSP_STATE *dsp_state, FMOD_BOOL inputsidle, unsigned int length, FMOD_CHANNELMASK inmask, int inchannels, FMOD_SPEAKERMODE speakermode)
{
	Plugin *dsp = (Plugin *)dsp_state->plugindata;
	if (inputsidle)
		return FMOD_ERR_DSP_DONTPROCESS;
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK readCallback(FMOD_DSP_STATE *dsp_state, float *inbuffer, float *outbuffer, unsigned int length, int inchannels, int *outchannels)
{
	Plugin *dsp = (Plugin *)dsp_state->plugindata;
	dsp->Process(inbuffer, outbuffer, length, inchannels);
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK setParameterFloat(FMOD_DSP_STATE *dsp_state, int index, float value)
{
	Plugin *dsp = (Plugin *)dsp_state->plugindata;
	dsp->setParameterFloat(index, value);
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK getParameterFloat(FMOD_DSP_STATE *dsp_state, int index, float *value, char *valuestr)
{
	Plugin *dsp = (Plugin *)dsp_state->plugindata;
	dsp->getParameterFloat(index, value, valuestr);
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK sysRegister(FMOD_DSP_STATE * /*dsp_state*/)
{
	isRunning = true;
	// called once for this type of dsp being loaded or registered (it is not per instance)
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK sysDeregister(FMOD_DSP_STATE * /*dsp_state*/)
{
	isRunning = false;
	// called once for this type of dsp being unloaded or de-registered (it is not per instance)
	return FMOD_OK;
}

FMOD_RESULT F_CALLBACK sysMix(FMOD_DSP_STATE * /*dsp_state*/, int /*stage*/)
{
	// stage == 0 , before all dsps are processed/mixed, this callback is called once for this type.
	// stage == 1 , after all dsps are processed/mixed, this callback is called once for this type.
	return FMOD_OK;
}



