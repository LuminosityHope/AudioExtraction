#pragma once
#include <vector>
#include <algorithm>
std::vector<float> convertToFloat(const std::vector<_int32>& signal) {
    float max_val = *std::max_element(signal.begin(), signal.end(),
        [](_int32 a, _int32 b) { return std::abs(a) < std::abs(b); });



    std::vector<float> result(signal.size());
    for (size_t i = 0; i < signal.size(); ++i) {
        result[i] = signal[i] / max_val; // Нормализация в [-1.0, 1.0]
    }
    return result;
}