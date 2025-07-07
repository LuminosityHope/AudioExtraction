#include "FromInt32ToFloat.h"
#include <algorithm>
#include <cmath> 

std::vector<float> convertToFloat(const std::vector<int32_t>& signal) {
    if (signal.empty()) {
        return {};
    }

    int32_t intmaxVal = *std::max_element(signal.begin(), signal.end(),
        [](int32_t a, int32_t b) { return std::abs(a) < std::abs(b); });
    float maxVal = static_cast<float>(intmaxVal);
    std::vector<float> result(signal.size());
    for (size_t i = 0; i < signal.size(); ++i) {
        result[i] = static_cast<float>(signal[i]) / maxVal;
    }
    return result;
}
