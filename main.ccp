#include "FileManager.h"
#include "Demodulator.h"
#include "downsample.h"
#include "filter.h"
#include "Wav.h"
#include "FromInt32ToFloat.h"


int main()
{
	auto am = FileManager::ReadSignal<_int32>("am_sound (1).dat");
	auto cam = FileManager::ReadComplex(am);
	DemodulatorAM<_int32> amDemodulator;
	auto demodSignal = amDemodulator.demodulate(cam);
	auto float_data = convertToFloat(demodSignal);
	saveToWavFloat(float_data, "output_32float.wav", 16000);


	auto fm = FileManager::ReadSignal<float>("file1EuropaPlus (1).bin");
	auto cfm = FileManager::ReadComplex(fm);
	DemodulatorFM<float> fmDemodulator;
	auto demodFmSignal = fmDemodulator.demodulate(cfm);
	Filter FmF(15, "fir");  
	auto FmfSignal = FmF.filtration(demodFmSignal);
	auto DSsignal = DownSample(FmfSignal, 16);
	saveToWavFloat(DSsignal, "test32.wav", 500000 / 16);  
	FileManager::SaveSignal(DSsignal, "FM_sound.bin");
	std::cout << "Successfully demodulated and saved "
		<< DSsignal.size() << " samples" << std::endl;
	
	return 0;
}
