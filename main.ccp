#include "FileManager.h"
#include "Demodulator.h"
#include "downsample.h"
#include "filter.h"
#include "Wav.h"
#include "FromInt32ToFloat.h"


int main()
{
	auto AMSignal = FileManager::ReadSignal<_int32>("am_sound (1).dat");
	auto ComplexAmSignal = FileManager::ReadComplex(AMSignal);
	DemodulatorAM<_int32> amDemodulator;
	auto demodSignal = amDemodulator.demodulate(ComplexAmSignal);
	auto FloatSignal = convertToFloat(demodSignal);
	saveToWavFloat(FloatSignal, "output_am_sound.wav", 16000);
	FileManager::SaveSignal(FloatSignal, "FM_sound.bin");
	std::cout << "Successfully demodulated and saved "
		<< FloatSignal.size() << " samples" << std::endl;

	auto FmSignal = FileManager::ReadSignal<float>("file1EuropaPlus (1).bin");
	auto ComplexFmSignal = FileManager::ReadComplex(FmSignal);
	DemodulatorFM<float> fmDemodulator;
	auto DemodFmSignal = fmDemodulator.demodulate(ComplexFmSignal);
	Filter FiltetedFM(15, "fir");  
	auto FmfSignal = FiltetedFM.filtration(DemodFmSignal);
	auto dsSignal = DownSample(FmfSignal, 16);
	saveToWavFloat(dsSignal, "output_file1EuropaPlus.wav", 500000 / 16);
	FileManager::SaveSignal(dsSignal, "FM_sound.bin");
	std::cout << "Successfully demodulated and saved "
		<< dsSignal.size() << " samples" << std::endl;
	
	return 0;
}
