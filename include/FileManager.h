#include <vector>
#include <complex>
#include <iostream>
#include <fstream>
#include <string>
class FileManager
{
public:

	template<typename T>
	static  std::vector<std::complex<T>> ReadSignal(const std::string& FileName)
	{
		std::ifstream file;
		file.open(FileName, std::ios::binary);
		if (!file.is_open())
		{
			throw std::runtime_error("File opening error " + FileName);
		}

		file.seekg(0, std::ios::end);
		size_t SizeOfFIle = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<T> signal(SizeOfFIle / sizeof(T));
		file.read(reinterpret_cast<char*>(signal.data()), SizeOfFIle);
		if (!file)
		{
			throw std::runtime_error("Error reading from a file " + FileName);
		}

		if (signal.size() % 2 != 0)
		{
			throw std::runtime_error("The signal size must be even.");
		}
		std::vector<std::complex<T>> ComplexSignal;
		ComplexSignal.reserve(signal.size() / 2);

		for (size_t i = 0; i < signal.size(); i += 2)
		{
			ComplexSignal.emplace_back(signal[i], signal[i + 1]);
		}

		file.close();

		return ComplexSignal;
	}

	template<typename T>
	static void SaveSignal(const std::vector<T>& SaveSignal, const std::string& OutPutFileName)
	{
		std::ofstream file(OutPutFileName, std::ios::binary);
		if (!file.is_open())
		{
			throw std::runtime_error("File opening error " + OutPutFileName);
		}
		file.write(reinterpret_cast<const char*>(SaveSignal.data()), SaveSignal.size() * sizeof(T));
		if (!file)
		{
			throw std::runtime_error("Error writing to a file " + OutPutFileName);
		}
	}


};
