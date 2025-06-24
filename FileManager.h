#include <vector>
#include <complex>
#include <iostream>
#include <fstream>
#include <string>
class FileManager
{ 
public:

	template<typename T>
	static  std::vector <T> ReadSignal(const std::string& FileName)
	{
		std::ifstream file;
		file.open(FileName, std::ios::binary );
		if (!file.is_open())
		{
			std::cout << "File not open" << std::endl;
		}
		file.seekg(0, std::ios::end);
		size_t SizeOfFIle = file.tellg();
		file.seekg(0, std::ios::beg);
		std::vector<T> Signal(SizeOfFIle / sizeof(T));
		file.read(reinterpret_cast<char*>(Signal.data()), SizeOfFIle);
		if (!file)
		{
			std::cout << "File error - can't open to read data!";
		}
		file.close();
		return  Signal;
	}

	template <typename T>
	static std::vector<std::complex<T>> ReadComplex( std::vector <T> Signal)
	{
		if (Signal.size() % 2 != 0)
		{
			std::cout << "Error of size";
		}
		std::vector<std::complex<T>> ComplexSignal;
		ComplexSignal.reserve(Signal.size() / 2);
		for (int i = 0; i < Signal.size(); i+=2)
		{
			ComplexSignal.emplace_back(Signal[i], Signal[i + 1]);
		}
		return ComplexSignal;

	}
	

	template<typename T>
	static void SaveSignal(const std::vector<T>& SaveSignal, const std::string& OutPutFileName)
	{
		std::ofstream file;
		file.open(OutPutFileName, std::ios::binary);
		if (!file.is_open())
		{
			std::cout << "File not open" << std::endl;
		}
		file.write(reinterpret_cast<const char*>(SaveSignal.data()), SaveSignal.size()*sizeof(T));
		if (!file)
		{
			std::cout << "File error - can't open to write data!";
		}
	}


};
