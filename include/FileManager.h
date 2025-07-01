#pragma once 

#include <vector>
#include <complex>
#include <iostream>
#include <fstream>
#include <string>

class FileManager
{
public:

	template<typename T>
	static  std::vector<std::complex<T>> ReadSignal(const std::string& fileName) //Static использую,потому не нужны обьекты класса
	{
		std::ifstream file;
		file.open(fileName, std::ios::binary);
		if (!file.is_open())
		{
			throw std::runtime_error("File opening error " + fileName);
		}

		file.seekg(0, std::ios::end);
		size_t sizeOffile = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<T> signal(sizeOffile / sizeof(T));
		file.read(reinterpret_cast<char*>(signal.data()), sizeOffile);
		if (!file)
		{
			throw std::runtime_error("Error reading from a file " + fileName);
		}

		if (signal.size() % 2 != 0)
		{
			throw std::runtime_error("The signal size must be even.");
		}
		std::vector<std::complex<T>> complexSignal;
		complexSignal.reserve(signal.size() / 2);

		for (size_t i = 0; i < signal.size(); i += 2)
		{
			complexSignal.emplace_back(signal[i], signal[i + 1]);
		}

		file.close();

		return complexSignal;
	}

	template<typename T>
	static void SaveSignal(const std::vector<T>& saveSignal, const std::string& outPutfileName)
	{
		std::ofstream file(outPutfileName, std::ios::binary);
		if (!file.is_open())
		{
			throw std::runtime_error("File opening error " + outPutfileName);
		}
		file.write(reinterpret_cast<const char*>(saveSignal.data()), saveSignal.size() * sizeof(T));
		if (!file)
		{
			throw std::runtime_error("Error writing to a file " + outPutfileName);
		}
	}
};
