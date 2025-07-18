#include "FromInt32ToFloat.h"
#include <algorithm>
#include <cmath> 

std::vector<float> convertToFloat(const std::vector<float>& signal) {
    if (signal.empty()) {
        return {};
    }

    float maxVal = *std::max_element(signal.begin(), signal.end(),
        [](float a, float b) { return std::abs(a) < std::abs(b); });
    std::vector<float> result(signal.size());
    for (size_t i = 0; i < signal.size(); ++i) {
        result[i] = (signal[i]) / maxVal;
    }
    return result;
}
