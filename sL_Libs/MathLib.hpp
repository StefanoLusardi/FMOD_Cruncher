#pragma once

#include <cmath>
#include <math.h>
#include <string.h>
#include <stdio.h>

class MathLib
{
public:
	/*   Constants   */
	static float constexpr MinGain_dB = -80.0f;
	static float constexpr MaxGain_dB = 12.0;
	static float constexpr ZeroGain_dB = 0.0f;
				 
	static float constexpr MinGain_lin = 0.0f;
	static float constexpr MaxGain_lin = 1.0f;
	static float constexpr ZeroGain_lin = 1.0f;
				 
	static float constexpr Pi = 3.14159265359;
	

	/*   Functions   */
	inline static float MathLib::dBToLin(float value_dB)
	{
		return (value_dB <= MathLib::MinGain_dB) ? 0.0f : powf(10.0f, value_dB / 20.0f);
	}

	inline static float MathLib::LinTodB(float value_lin)
	{
		return (value_lin <= MathLib::MinGain_lin) ? MathLib::MinGain_dB : 20.0 * log10f(value_lin);
	}

	inline static float MathLib::GetRandomFloat(void)
	{
		return (static_cast<float>(rand() % 32768) / 16384.0f - 1.0f);
	}

	//inline static float dBToLin(float value_dB);
	//inline static float LinTodB(float value_lin);
	//inline static float GetRandomFloat(void);
};

// Remove
#define DECIBELS_TO_LINEAR(__dbval__)  ((__dbval__ <= -80.0f) ? 0.0f : powf(10.0f, __dbval__ / 20.0f))
#define LINEAR_TO_DECIBELS(__linval__) ((__linval__ <= 0.0f) ? -80.0f : 20.0f * log10f((float)__linval__))
#define INTERPOLATION_SAMPLES 256
