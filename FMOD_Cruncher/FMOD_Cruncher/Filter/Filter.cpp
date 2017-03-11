#include "Filter.hpp"

Filter::Filter()
{
	mTargetResonance = 1.0f;
	mTargetCutoff = 22000.0f;

	mProtoCoef[0].a0 = 1.0f;
	mProtoCoef[0].a1 = 0;
	mProtoCoef[0].a2 = 0;
	mProtoCoef[0].b0 = 1.0f;
	mProtoCoef[0].b1 = 0.765367f;
	mProtoCoef[0].b2 = 1.0f;
	mGainFactor[0] = 1.0f;

	mProtoCoef[1].a0 = 1.0f;
	mProtoCoef[1].a1 = 0;
	mProtoCoef[1].a2 = 0;
	mProtoCoef[1].b0 = 1.0f;
	mProtoCoef[1].b1 = 1.847759f;
	mProtoCoef[1].b2 = 1.0f;
	mGainFactor[1] = 1.0f;

	Filter::Reset();
}

Filter::~Filter()
{
}

void Filter::ProcessAudioBuffer(float* inBuffer, float* outBuffer, unsigned length, int channels)
{
	if (!inBuffer)
	{
		return;
	}

	while ((mCurrentResonance != mTargetResonance || mCurrentCutoff != mTargetCutoff) && length)
	{
		float deltaCutoff = 10.0f + (mCurrentCutoff / 100.0f);
		float deltaResonance = mCurrentResonance / 10.0f;

		if (mCurrentResonance < mTargetResonance)
		{
			mCurrentResonance += deltaResonance;
			if (mCurrentResonance >= mTargetResonance)
			{
				mCurrentResonance = mTargetResonance;
			}
		}
		else if (mCurrentResonance > mTargetResonance)
		{
			mCurrentResonance -= deltaResonance;
			if (mCurrentResonance <= mTargetResonance)
			{
				mCurrentResonance = mTargetResonance;
			}
		}

		if (mCurrentCutoff < mTargetCutoff)
		{
			mCurrentCutoff += deltaCutoff;
			if (mCurrentCutoff >= mTargetCutoff)
			{
				mCurrentCutoff = mTargetCutoff;
			}
		}
		else if (mCurrentCutoff > mTargetCutoff)
		{
			mCurrentCutoff -= deltaCutoff;
			if (mCurrentCutoff <= mTargetCutoff)
			{
				mCurrentCutoff = mTargetCutoff;
			}
		}

		UpdateState(mCurrentResonance, mCurrentCutoff);

		ProcessAudioChannel(inBuffer, outBuffer, 1, channels);

		inBuffer += channels;
		outBuffer += channels;
		length--;
	}

	return ProcessAudioChannel(inBuffer, outBuffer, length, channels);
}

void Filter::ProcessAudioChannel(float* inBuffer, float* outBuffer, unsigned length, int channels)
{
	for (unsigned int sample = 0; sample < length; sample++)
	{
		for (unsigned int ch = 0; ch < channels; ch++)
		{
			*outBuffer++ = ProcessAudioSample(*inBuffer++, nullptr, ch);
		}
	}
}

inline float Filter::ProcessAudioSample(float input, iDspParams* /*params*/, unsigned int channel)
{
	float *history1, *history2, *coef_ptr;
	float output, new_hist;
	static float dc = static_cast<float>(1E-20);

	input += dc;
	dc = -dc;

	coef_ptr = mCoefficients;

	history1 = mHistory[channel];	
	history2 = history1 + 1;	

	output = input * (*coef_ptr++);

	for (int i = 0; i < FILTER_ORDER; i++)
	{
		output   = output   - history1[0] * coef_ptr[0];
		new_hist = output   - history2[0] * coef_ptr[1];
		output   = new_hist + history1[0] * coef_ptr[2];
		output   = output   + history2[0] * coef_ptr[3];

		coef_ptr += 4;
		*history2++ = *history1;
		*history1++ = new_hist;
		history1++;
		history2++;
	}

	return output;
}

void Filter::Reset()
{
	mCurrentCutoff = mTargetCutoff;
	mCurrentResonance = mTargetResonance;
	mInterpolationSamples = 0;

	memset(mHistory, 0, DSP_MAX_CHANNELS * 2 * FILTER_ORDER * sizeof(float));

	UpdateState(mCurrentResonance, mCurrentCutoff);
}

float Filter::getCutoff()
{
	return mCurrentCutoff;
}

void Filter::setCutoff(float cutoff)
{
	mTargetCutoff = cutoff;
	mInterpolationSamples = MathLib::InterpolationSamples;
}

float Filter::getResonance()
{
	return  mCurrentResonance;
}

void Filter::setResonance(float resonance)
{
	mTargetResonance = resonance;
	mInterpolationSamples = MathLib::InterpolationSamples;
}

void Filter::UpdateState(float resonance, float cutoff)
{	
	float a0, a1, a2, b0, b1, b2;
	float *coef;				
	float filterGain = 1.0f;	
	float sampleRate = 48000.0f;
	std::vector<float> sectionsGain(2, 1.0f);

	coef = mCoefficients + 1;		

	for (int section = 0; section < FILTER_ORDER; section++)
	{
		a0 = mProtoCoef[section].a0;
		a1 = mProtoCoef[section].a1;
		a2 = mProtoCoef[section].a2;

		b0 = mProtoCoef[section].b0;
		b1 = mProtoCoef[section].b1 / resonance;
		b2 = mProtoCoef[section].b2;

		szTransform(&a0, &a1, &a2, &b0, &b1, &b2, cutoff, sampleRate, &sectionsGain[section], coef);

		if (mGainFactor[section] != 0.0f)
		{
			for (int ch = 0; ch < DSP_MAX_CHANNELS; ch++)
			{
				mHistory[ch][section] *= sectionsGain[section] / mGainFactor[section];
			}
		}
		mGainFactor[section] = sectionsGain[section];
		filterGain *= sectionsGain[section];		
		coef += 4;									
	}

	mCoefficients[0] = filterGain;	

}

void Filter::szTransform(float *a0, float *a1, float *a2, float *b0, float *b1, float *b2, float fc, float fs, float *k, float *coef)
{
	Prewarp(a0, a1, a2, fc, fs);
	Prewarp(b0, b1, b2, fc, fs);
	Bilinear(*a0, *a1, *a2, *b0, *b1, *b2, k, fs, coef);
}

void Filter::Bilinear(float a0, float a1, float a2, float b0, float b1, float b2, float *k, float fs, float *coef)
{
	float bd = 4.0f * b2 * fs * fs + 2.0f * b1 * fs + b0;
	float ad = 4.0f * a2 * fs * fs + 2.0f * a1 * fs + a0;

	*coef++ = (2.0f * b0 - 8.0f * b2 * fs * fs) / bd;			
	*coef++ = (4.0f * b2 * fs * fs - 2.0f * b1 * fs + b0) / bd;

	*coef++ = (2.0f * a0 - 8.0f * a2 * fs * fs) / ad;			
	*coef   = (4.0f * a2 * fs * fs - 2.0f * a1 * fs + a0) / ad;

	*k *= ad / bd;
}

void Filter::Prewarp(float* /*a0*/, float *a1, float *a2, float fc, float fs)
{
	double wp = 2.0f * fs * std::tan(MathLib::Pi * fc / fs);

	*a2 = (*a2) / (wp * wp);
	*a1 = (*a1) / wp;
}
