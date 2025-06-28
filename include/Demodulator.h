#include <vector>
#include <complex>
#include <cmath>
template <typename T>
class Demodulator
{
public:
	virtual ~Demodulator() = default;
	virtual std::vector<T> demodulate(const std::vector<std::complex<T>>& signal) = 0;
};

template <typename T>
class DemodulatorAM :public Demodulator<T>
{
public:
	std::vector<T> demodulate(const std::vector<std::complex<T>>& signal)
	{
		std::vector<T> demodulatedSignal;
		demodulatedSignal.reserve(signal.size());
		for (size_t i = 0; i < signal.size(); ++i)
		{
			demodulatedSignal.emplace_back(std::abs(signal[i]));
		}
		return demodulatedSignal;
	}
};

template <typename T>
class DemodulatorFM : public Demodulator<T>
{
public:
	std::vector<T> demodulate(const std::vector<std::complex<T>>& signal)
	{
		std::vector<T> demodulatedSignal;
		demodulatedSignal.reserve(signal.size() - 1);

		for (size_t i = 1; i <= signal.size() - 1; ++i)
		{
			demodulatedSignal.push_back(std::arg(signal[i] * std::conj(signal[i - 1])));

		}
		return demodulatedSignal;
	}
};
