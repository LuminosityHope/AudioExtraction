#include "Wav.h"
#include <fstream>

void saveToWavFloat(const std::vector<float>& signal, const std::string& filename, uint32_t sampleRate)
{
    WAV_HEADER_FLOAT header;
    header.SamplesPerSec = sampleRate;
    header.Subchunk2Size = signal.size() * sizeof(float);
    header.ChunkSize = header.Subchunk2Size + sizeof(header) - 8;
    header.bytesPerSec = sampleRate * sizeof(float);
    header.blockAlign = sizeof(float);

    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("File opening error " + filename);
    }
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
    if (!file) {
        throw std::runtime_error("Header data recording error to file: " + filename);
    }
    file.write(reinterpret_cast<const char*>(signal.data()), header.Subchunk2Size);
    if (!file) {
        throw std::runtime_error("Audio data recording error  to file: " + filename);
    }
}
