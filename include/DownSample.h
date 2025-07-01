#pragma once
#include <vector>



template <typename T>
std::vector<T> DownSample(std::vector<T>& signal, size_t samplingOrder)
{
	std::vector<T> outPut;
	outPut.reserve((signal.size() + samplingOrder - 1) / samplingOrder);
	for (size_t i = 0; i < signal.size(); i += samplingOrder)
	{
		outPut.emplace_back(signal[i]);
	}
	return outPut;
}