#ifndef WAV_H

#define WAV_H

#include <vector>
#include <string>
#include <cstdint>
struct WAV_HEADER_FLOAT {
    uint8_t RIFF[4] = { 'R','I','F','F' };
    uint32_t ChunkSize;
    uint8_t WAVE[4] = { 'W','A','V','E' };
    uint8_t fmt[4] = { 'f','m','t',' ' };
    uint32_t Subchunk1Size = 16;
    uint16_t AudioFormat = 3;    // 3 = IEEE float
    uint16_t NumOfChan = 1;
    uint32_t SamplesPerSec;
    uint32_t bytesPerSec;
    uint16_t blockAlign;
    uint16_t bitsPerSample = 32;
    uint8_t Subchunk2ID[4] = { 'd','a','t','a' };
    uint32_t Subchunk2Size;
};


void saveToWavFloat(const std::vector<float>& signal, const std::string& filename, uint32_t sampleRate);

#endif