#include "Plugin.hpp"

void Plugin::Create()
{
	dspGain			= new Gain();
	dspNoise		= new Noise();
	dspDistortion	= new Distortion();
	dspBitCrush		= new BitCrusher();
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

	if (dspBitCrush)
	{
		dspBitCrush->Release();
		delete dspBitCrush;
	}	
}

void Plugin::Process(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	int numSamples = length * channels;

	bufGain.resize(numSamples);
	dspGain->ProcessAudioBuffer(inBuffer, &bufGain[0], length, channels);		

	bufNoise.resize(numSamples);
	dspNoise->ProcessAudioBuffer(&bufGain[0], &bufNoise[0], length, channels);	

	bufDistortion.resize(numSamples);
	dspDistortion->ProcessAudioBuffer(&bufNoise[0], &bufDistortion[0], length, channels);

	dspBitCrush->ProcessAudioBuffer(&bufDistortion[0], outBuffer, length, channels);
}

void Plugin::Reset()
{
	if (dspGain)
		delete dspGain;

	if (dspNoise)
		delete dspNoise;

	if (dspDistortion)
		delete dspDistortion;

	if (dspBitCrush)
		delete dspBitCrush;

	dspGain			= new Gain();
	dspNoise		= new Noise();
	dspDistortion	= new Distortion();
	dspBitCrush		= new BitCrusher();

	bufGain.clear();
	bufNoise.clear();
	bufDistortion.clear();
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
				
	case static_cast<int>(UiParams::UI_PARAM_DECIMATION) :
		if (dspBitCrush)
			(static_cast<BitCrusher*>(dspBitCrush))->setDecimation(value);
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

	case static_cast<int>(UiParams::UI_PARAM_DECIMATION) :
		*value = (static_cast<BitCrusher*>(dspBitCrush))->getDecimation();
		if (valuestr)
			sprintf(valuestr, "%.1f dB", (static_cast<BitCrusher*>(dspBitCrush))->getDecimation());
		break;

	default:
		break;
	}
}

void Plugin::setParameterInt(int index, int value)
{
	switch (index)
	{
	case static_cast<int>(UiParams::UI_PARAM_BIT_DEPTH) :
		if (dspBitCrush)
			(static_cast<BitCrusher*>(dspBitCrush))->setBits(value);
		break;

	default: 
		break;
	}
}

void Plugin::getParameterInt(int index, int * value, char * valuestr)
{
	switch (index)
	{
	case static_cast<int>(UiParams::UI_PARAM_BIT_DEPTH) :
		*value = (static_cast<BitCrusher*>(dspBitCrush))->getBits();
		if (valuestr)
			sprintf(valuestr, "%d dB", (static_cast<BitCrusher *>(dspBitCrush))->getBits());
		break;

	default:
		break;
	}
}

//void Plugin::setParameterBool(int index, bool value)
//{
//}
//
//void Plugin::getParameterBool(int index, bool * value, char * valuestr)
//{
//}

