#pragma once

#include <vector>
#include <complex>
#include <cmath>
template <typename T>
class Demodulator
{
public:
    virtual ~Demodulator() = default;
    virtual std::vector<float> demodulate(const std::vector<std::complex<T>>& signal) = 0;
};


template <typename T>
class DemodulatorAM :public Demodulator<T>
{
public:
    ~DemodulatorAM() override = default;
    std::vector<float> demodulate(const std::vector<std::complex<T>>& signal)
    {
        std::vector<float> demodulatedSignal;
        demodulatedSignal.reserve(signal.size());

        for (size_t i = 0; i < signal.size(); ++i)
        {
            float real = static_cast<float>(signal[i].real());
            float imag = static_cast<float>(signal[i].imag());
            float module = std::sqrt(real * real + imag * imag);
            demodulatedSignal.emplace_back(module);
        }

        return demodulatedSignal;
    }
};

template <typename T>
class DemodulatorFM : public Demodulator<T>
{
public:
	~DemodulatorFM() override = default;
	std::vector<float> demodulate(const std::vector<std::complex<T>>& signal)
	{
		std::vector<float> demodulatedSignal;
		demodulatedSignal.reserve(signal.size() - 1);

		for (size_t i = 1; i <= signal.size() - 1; ++i)
		{
			demodulatedSignal.push_back(std::arg(signal[i] * std::conj(signal[i - 1])));

		}
		return demodulatedSignal;
	}
};
