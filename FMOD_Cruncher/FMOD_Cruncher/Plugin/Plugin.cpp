#include "Plugin.hpp"
#include <vector>

void Plugin::Create()
{
	dspGain  = new Gain();
	dspNoise = new Noise();
	dspDistortion = new Distortion();
}

void Plugin::Release()
{
	if (dspGain)
	{
		dspGain->Release();
		delete dspGain;
	}

	if (dspNoise)
	{
		dspNoise->Release();
		delete dspNoise;
	}

	if (dspDistortion)
	{
		dspDistortion->Release();
		delete dspDistortion;
	}
}

void Plugin::Process(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	int numSamples = length * channels;
	std::vector<float> bufferOutputGain(numSamples);
	//float bufferOutputGain[2048];
	dspGain->ProcessAudioBuffer(inBuffer, &bufferOutputGain[0], length, channels);	
	
	//float bufferOutputNoise[2048];
	//dspNoise->ProcessAudioBuffer(&bufferOutputGain[0], outBuffer, length, channels);
	std::vector<float> bufferOutputNoise(numSamples);
	dspNoise->ProcessAudioBuffer(&bufferOutputGain[0], &bufferOutputNoise[0], length, channels);

	std::vector<float> bufferOutputDistortion(numSamples);
	dspDistortion->ProcessAudioBuffer(&bufferOutputNoise[0], outBuffer, length, channels);
}

void Plugin::Reset()
{
	if (dspGain)
		delete dspGain;

	if (dspNoise)
		delete dspNoise;

	if (dspDistortion)
		delete dspDistortion;

	dspGain  = new Gain();
	dspNoise = new Noise();
	dspDistortion = new Distortion();
}

void Plugin::setParameterFloat(int index, float value)
{
	switch (index)
	{
	case static_cast<int>(UiParams::UI_PARAM_GAIN) :
		if (dspGain)
			(static_cast<Gain*>(dspGain))->setGain(value);
		break;

	case static_cast<int>(UiParams::UI_PARAM_NOISE_AMP) :
		if (dspNoise)
			(static_cast<Noise*>(dspNoise))->setAmp(value);
		break;

	case static_cast<int>(UiParams::UI_PARAM_DISTORTION) :
		if (dspDistortion)
			(static_cast<Distortion*>(dspDistortion))->setLevel(value);
		break;

	default: 
		break;
	}
}

void Plugin::getParameterFloat(int index, float * value, char * valuestr)
{
	switch (index)
	{
	case static_cast<int>(UiParams::UI_PARAM_GAIN) :
		*value = (static_cast<Gain*>(dspGain))->getGain();
		if (valuestr) 
			sprintf(valuestr, "%.1f dB", (static_cast<Gain *>(dspGain))->getGain());
		break;

	case static_cast<int>(UiParams::UI_PARAM_NOISE_AMP) :
		*value = (static_cast<Noise*>(dspNoise))->getAmp();
		if (valuestr)
			sprintf(valuestr, "%.1f dB", (static_cast<Noise*>(dspNoise))->getAmp());
		break;

	case static_cast<int>(UiParams::UI_PARAM_DISTORTION) :
		*value = (static_cast<Distortion*>(dspDistortion))->getLevel();
		if (valuestr)
			sprintf(valuestr, "%.1f dB", (static_cast<Distortion*>(dspDistortion))->getLevel());
		break;

	default:
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
