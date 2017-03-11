#pragma once

#include <cmath>
#include <math.h>
#include <string.h>
#include <stdio.h>

namespace MathLib
{
	/*   Constants   */
	static float const MinGain_dB = -80.0f;
	static float const MaxGain_dB = 12.0;
	static float const ZeroGain_dB = 0.0f;
	
	static float const MinGain_lin = 0.0f;
	static float const MaxGain_lin = 1.0f;
	static float const ZeroGain_lin = 1.0f;
	
	static float const Pi = 3.14159265359f;

	static int const InterpolationSamples = 256;
	

	/*   Functions   */
	float dBToLin(float value_dB);
	float LinTodB(float value_lin);
	float GetRandomFloat();
}
