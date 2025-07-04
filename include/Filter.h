#pragma once
#include <vector>
#include <iostream>
enum class TypeFilter { FIR, IIR };
class Filter {
public:
    Filter(size_t windSize, TypeFilter type);
    ~Filter();
    template <typename T>
    std::vector<T> filtration(const std::vector<T>& signal);
    
private:
    size_t windowSize;
    TypeFilter filterType;

};

template <typename T>
std::vector<T> Filter::filtration(const std::vector<T>& signal) {
    std::vector <T> outPut;
    const double fraction = double(double(1)/ windowSize);
    switch (filterType)
    {
    case TypeFilter::FIR:
        outPut.reserve(signal.size() - windowSize + 1);
        for (size_t i = 0; i <= signal.size() - windowSize; ++i)
        {
            T sum = 0;
            for (size_t j = i; j < i + windowSize; ++j)
            {
                sum += signal[j];
            }
            outPut.emplace_back(sum / windowSize);
        }
        return outPut;
    case TypeFilter::IIR:
        outPut.reserve(signal.size());
        
        for (size_t i = 0; i < signal.size(); ++i)
        {
            if (i < windowSize || windowSize==1)
            {
                outPut.emplace_back((signal[i]/windowSize));
            }
            else 
            {
                outPut.emplace_back(outPut[i - 1] + (fraction) * (signal[i] - signal[i - windowSize]));
            }
        }
        return outPut;
    default:
        std::cout << "You can choose only FIR or IIR";
    }    
}
