#include "CMakeAudio.h"

int main() {
    try {
        try {
            auto AMSignal = FileManager::ReadSignal<int32_t>("data/am_sound_1.dat");
            DemodulatorAM<int32_t> amDemodulator;
            auto demodSignal = amDemodulator.demodulate(AMSignal);
            auto FloatSignal = convertToFloat(demodSignal);
            saveToWavFloat(FloatSignal, "Makarena.wav", 16000);
        }
        catch (const std::exception& err) {
            std::cerr << "AM processing error: " << err.what() << std::endl;
            return 1;
        }
        try {
            auto FmSignal = FileManager::ReadSignal<float>("data/file1EuropaPlus_1.bin");
            DemodulatorFM<float> fmDemodulator;
            auto DemodFmSignal = fmDemodulator.demodulate(FmSignal);
            Filter FiltetedFM(15, "fir");
            auto FmfSignal = FiltetedFM.filtration(DemodFmSignal);
            auto dsSignal = DownSample(FmfSignal, 16);
            saveToWavFloat(dsSignal, "Pugacheva.wav", 500000 / 16);
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




