#pragma once

#include "iDspInterface.hpp"

class Distortion : iDspInterface
{
public:
	Distortion();
	float getAmount() { return mDistortion; };
	void  setAmount(float distortion) { mDistortion = distortion; };

private:
	float mDistortion;
};