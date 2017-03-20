#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "../../../FMOD_Lib/fmod.hpp"
#include "../Plugin/PluginParams.hpp"
#include "../Gain/Gain.hpp"
#include "../Noise/Noise.hpp"
#include "../Distortion/Distortion.hpp"
#include "../BitCrusher/BitCrusher.hpp"
#include "../Filter/Filter.hpp"
#include <memory>


// TODO: Plugin Interface implementation??
class Plugin// : iPluginInterface
{
public:
	Plugin() :	dspGain(nullptr),
				dspNoise(nullptr), 
				dspBitCrush(nullptr), 
				dspDistortion(nullptr),
				dspFilter(nullptr),
				mBypass(false)
	{ }

	void Create();
	void Create(FMOD_DSP_STATE*);
	void Reset(); 
	void Process(float *inBuffer, float *outBuffer, unsigned int length, int channels);
	void Bypass(float *inBuffer, float *outBuffer, unsigned int length, int channels) const;
	
	bool getBypass();
	void setBypass(bool);

	void setParameterFloat(int index, float value);
	void getParameterFloat(int index, float *value, char *valuestr);
	void setParameterInt(int index, int value);
	void getParameterInt(int index, int *value, char *valuestr);

private:
	std::unique_ptr<iDspInterface> dspGain;
	std::unique_ptr<iDspInterface> dspNoise;
	std::unique_ptr<iDspInterface> dspBitCrush;
	std::unique_ptr<iDspInterface> dspDistortion;
	std::unique_ptr<iDspInterface> dspFilter;

	std::vector<float> bufGain;
	std::vector<float> bufNoise;
	std::vector<float> bufBitCrusher;
	std::vector<float> bufDistortion;

	bool mBypass;
};

