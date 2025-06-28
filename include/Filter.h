#pragma once

#include <vector>
#include <string>

class Filter {
public:

    Filter(size_t windsize, std::string type): window_size(windsize), type_filt(type) {}
    ~Filter() = default;
    template <typename T>
    std::vector<T> filtration(std::vector<T>& signal) {
        {
            std::vector<T> output;
            output.reserve(signal.size() - window_size + 1);

            for (size_t i = 0; i <= signal.size() - window_size; ++i)
            {
                T sum = 0;
                for (size_t j = i; j < i + window_size; ++j)
                {
                    sum += signal[j];
                }
                output.emplace_back(sum / window_size);
            }

            return output;
        }
    }
private:
    size_t window_size;
    std::string type_filt;
};

