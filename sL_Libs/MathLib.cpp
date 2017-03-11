#include "MathLib.h"

namespace MathLib
{
	float dBToLin(float value_dB)
	{
		return (value_dB <= MinGain_dB) ? 0.0f : powf(10.0f, value_dB / 20.0f);
	}

	float LinTodB(float value_lin)
	{
		return (value_lin <= MinGain_lin) ? MinGain_dB : 20.0f * log10f(value_lin);
	}

	float GetRandomFloat()
	{
		return (static_cast<float>(rand() % 32768) / 16384.0f - 1.0f);
	}
}