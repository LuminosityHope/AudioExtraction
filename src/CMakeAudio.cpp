#include "CMakeAudio.h"

int main() {
    std::string amPath, fmPath;
    std::cout << "Enter AM signal file path: ";
    std::getline(std::cin, amPath);
    std::cout << "Enter FM signal file path: ";
    std::getline(std::cin, fmPath);
    try {
        try {
            auto amSignal = FileManager::ReadSignal<int32_t>(amPath);
            DemodulatorAM<int32_t> amDemodulator;
            auto demodSignal = amDemodulator.demodulate(amSignal);
            auto floatSignal = convertToFloat(demodSignal);
            saveToWavFloat(floatSignal, "Makarena3.wav", 16000);
        }
        catch (const std::exception& err) {
            std::cerr << "AM processing error: " << err.what() << std::endl;
            return 1;
        }
        try {
            auto fmSignal = FileManager::ReadSignal<float>(fmPath);
            DemodulatorFM<float> fmDemodulator;
            auto demodFmSignal = fmDemodulator.demodulate(fmSignal);
            Filter FiltetedFM(15, TypeFilter::IIR);
            auto fmfSignal = FiltetedFM.filtration(demodFmSignal);
            auto dsSignal = DownSample(fmfSignal, 16);
            saveToWavFloat(dsSignal, "Pugacheva3.wav", 500000 / 16);
        }
        catch (const std::exception& err) {
            std::cerr << "FM processing error: " << err.what() << std::endl;
            return 2;
        }
        std::cout << "All complete";
        return 0;
    }
    catch (...) {
        std::cerr << "Unknown error occurred!" << std::endl;
        return -1;
    }
}


