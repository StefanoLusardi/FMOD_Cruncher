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
			//((Gain *)dspGain)->setGain(value);
			(static_cast<Gain *>(dspGain))->setGain(value);
		break;
	}
}

void Plugin::getParameterFloat(int index, float * value, char * valuestr)
{
	switch (index)
	{
	case UI_PARAM_GAIN:
		*value = ((Gain *)dspGain)->getGain();
		if (valuestr) sprintf(valuestr, "%.1f dB", ((Gain *)dspGain)->getGain());
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
