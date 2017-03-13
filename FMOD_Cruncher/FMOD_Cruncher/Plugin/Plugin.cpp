#include "Plugin.hpp"

void Plugin::Create()
{
	dspGain = std::make_unique<Gain>();
	dspNoise = std::make_unique<Noise>();
	dspDistortion = std::make_unique<Distortion>();
	dspBitCrush = std::make_unique<BitCrusher>();
	dspFilter = std::make_unique<Filter>();
}

void Plugin::Release()
{
	//if (dspGain)
	//{
	//	dspGain->Release();
	//	delete dspGain;
	//}

	//if (dspNoise)
	//{
	//	dspNoise->Release();
	//	delete dspNoise;
	//}

	//if (dspDistortion)
	//{
	//	dspDistortion->Release();
	//	delete dspDistortion;
	//}

	//if (dspBitCrush)
	//{
	//	dspBitCrush->Release();
	//	delete dspBitCrush;
	//}	

	//if (dspFilter)
	//{
	//	dspFilter->Release();
	//	delete dspFilter;
	//}
}

void Plugin::Process(float * inBuffer, float * outBuffer, unsigned int length, int channels)
{
	int numSamples = length * channels;

	bufGain.resize(numSamples);
	dspGain->ProcessAudioBuffer(inBuffer, &bufGain[0], length, channels);		

	bufNoise.resize(numSamples);
	dspNoise->ProcessAudioBuffer(&bufGain[0], &bufNoise[0], length, channels);	

	bufBitCrusher.resize(numSamples);
	dspBitCrush->ProcessAudioBuffer(&bufNoise[0], &bufBitCrusher[0], length, channels);

	bufDistortion.resize(numSamples);
	dspDistortion->ProcessAudioBuffer(&bufBitCrusher[0], &bufDistortion[0], length, channels);
	
	dspFilter->ProcessAudioBuffer(&bufDistortion[0], outBuffer, length, channels);
}

void Plugin::Bypass(float *inBuffer, float *outBuffer, unsigned int length, int channels)
{
	memcpy(outBuffer, inBuffer, sizeof(float) * length * channels);
}

void Plugin::Reset()
{
	//if (dspGain)
	//	delete dspGain;

	//if (dspNoise)
	//	delete dspNoise;

	//if (dspDistortion)
	//	delete dspDistortion;

	//if (dspBitCrush)
	//	delete dspBitCrush;

	//if (dspFilter)
	//	delete dspFilter;

	dspGain = std::make_unique<Gain>();
	dspNoise = std::make_unique<Noise>();
	dspDistortion = std::make_unique<Distortion>();
	dspBitCrush = std::make_unique<BitCrusher>();
	dspFilter = std::make_unique<Filter>();

	bufGain.clear();
	bufNoise.clear();
	bufDistortion.clear();
}

bool Plugin::getBypass()
{
	return mBypass;
}

void Plugin::setBypass(bool bypass)
{
	mBypass = bypass;
}

void Plugin::setParameterFloat(int index, float value)
{
	switch (index)
	{
	case static_cast<int>(UiParams::UI_PARAM_GAIN) :
		if (dspGain)
			(static_cast<Gain*>(dspGain.get()))->setGain(value);
			//(static_cast<Gain*>(dspGain))->setGain(value);
		break;

	case static_cast<int>(UiParams::UI_PARAM_NOISE_AMP) :
		if (dspNoise)
			(static_cast<Noise*>(dspNoise.get()))->setAmp(value);
		break;

	case static_cast<int>(UiParams::UI_PARAM_DISTORTION) :
		if (dspDistortion)
			(static_cast<Distortion*>(dspDistortion.get()))->setLevel(value);
		break;
				
	case static_cast<int>(UiParams::UI_PARAM_DECIMATION) :
		if (dspBitCrush)
			(static_cast<BitCrusher*>(dspBitCrush.get()))->setDecimation(value);
		break;

	case static_cast<int>(UiParams::UI_PARAM_CUTOFF) :
		if (dspFilter)
			(static_cast<Filter*>(dspFilter.get()))->setCutoff(value);
		break;

	case static_cast<int>(UiParams::UI_PARAM_RESONANCE) :
		if (dspFilter)
			(static_cast<Filter*>(dspFilter.get()))->setResonance(value);
		break;

	case static_cast<int>(UiParams::UI_PARAM_BYPASS) :
		this->setBypass(static_cast<bool>(value));
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
		*value = (static_cast<Gain*>(dspGain.get()))->getGain();
		if (valuestr) 
			sprintf(valuestr, "%.1f dB", (static_cast<Gain *>(dspGain.get()))->getGain());
		break;

	case static_cast<int>(UiParams::UI_PARAM_NOISE_AMP) :
		*value = (static_cast<Noise*>(dspNoise.get()))->getAmp();
		if (valuestr)
			sprintf(valuestr, "%.1f dB", (static_cast<Noise*>(dspNoise.get()))->getAmp());
		break;

	case static_cast<int>(UiParams::UI_PARAM_DISTORTION) :
		*value = (static_cast<Distortion*>(dspDistortion.get()))->getLevel();
		if (valuestr)
			sprintf(valuestr, "%.1f dB", (static_cast<Distortion*>(dspDistortion.get()))->getLevel());
		break;

	case static_cast<int>(UiParams::UI_PARAM_DECIMATION) :
		*value = (static_cast<BitCrusher*>(dspBitCrush.get()))->getDecimation();
		if (valuestr)
			sprintf(valuestr, "%.1f dB", (static_cast<BitCrusher*>(dspBitCrush.get()))->getDecimation());
		break;

	case static_cast<int>(UiParams::UI_PARAM_CUTOFF) :
		*value = (static_cast<Filter*>(dspFilter.get()))->getCutoff();
		if (valuestr)
			sprintf(valuestr, "%.1f dB", (static_cast<Filter*>(dspFilter.get()))->getCutoff());
		break;

	case static_cast<int>(UiParams::UI_PARAM_RESONANCE) :
		*value = (static_cast<Filter*>(dspFilter.get()))->getResonance();
		if (valuestr)
			sprintf(valuestr, "%.1f dB", (static_cast<Filter*>(dspFilter.get()))->getResonance());
		break;

	case static_cast<int>(UiParams::UI_PARAM_BYPASS) :
		*value = this->getBypass();
		if (valuestr)
			sprintf(valuestr, "%d", this->getBypass());
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
			(static_cast<BitCrusher*>(dspBitCrush.get()))->setBits(value);
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
		*value = (static_cast<BitCrusher*>(dspBitCrush.get()))->getBits();
		if (valuestr)
			sprintf(valuestr, "%d dB", (static_cast<BitCrusher *>(dspBitCrush.get()))->getBits());
		break;

	default:
		break;
	}
}

