#pragma once
#include <vector>
#include <iostream>
#include <fstream>


template <typename T>
std::vector<T> DownSample(std::vector<T>& signal, size_t sampling_order)
{
	std::vector<T> output;
	output.reserve((signal.size() + sampling_order - 1) / sampling_order);
	for (size_t i = 0; i < signal.size(); i += sampling_order)
	{
		output.emplace_back(signal[i]);
	}
	return output;
}