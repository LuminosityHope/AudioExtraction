#include "gtest/gtest.h"
#include "Demodulator.h" 
#include <ccomplex>
#include <math.h>
#include <vector>
float const PI = 3.1415927f;
class DemodulatorTest : public::testing::Test
{
protected:
	virtual void SetUp(void)
	{
		dataFloat = { {1.1f,0.2f}, {2.3f, 4.1f}, {6.9f,4.5f} }; 
		dataInt = { {1,2 }, {5, 4}, {7,9}, {6,0} }; 
	}
	std::vector<std::complex<float>> dataFloat;
	std::vector<std::complex<int>>dataInt;
};
TEST_F(DemodulatorTest, DataCorrectlyAM)
{
	DemodulatorAM<int> demodInt;
	auto demod = demodInt.demodulate(dataInt);
	ASSERT_EQ(demod.size(), dataInt.size());
	EXPECT_FLOAT_EQ(demod[0], std::round(std::sqrt(1 * 1 + 2 * 2)));
	EXPECT_FLOAT_EQ(demod[1], std::round(std::sqrt(5 * 5 + 4 * 4)));
	EXPECT_FLOAT_EQ(demod[2], std::round(std::sqrt(7 * 7 + 9 * 9)));
	EXPECT_FLOAT_EQ(demod[3], std::round(std::sqrt(6 * 6 + 0 * 0)));

	DemodulatorAM<float> demodFloat;
	auto demodFl = demodFloat.demodulate(dataFloat);
	ASSERT_EQ(demodFl.size(), dataFloat.size());
	EXPECT_FLOAT_EQ(demodFl[0], (std::sqrtf(1.1f * 1.1f + 0.2f * 0.2f)));
	EXPECT_FLOAT_EQ(demodFl[1], (std::sqrtf(2.3f * 2.3f + 4.1f * 4.1f)));
	EXPECT_FLOAT_EQ(demodFl[2], (std::sqrtf(6.9f * 6.9f + 4.5f * 4.5f)));
}
TEST_F(DemodulatorTest, DataCorrectlyFM)
{
	DemodulatorFM<int> demodInt;
	auto demod = demodInt.demodulate(dataInt);
	ASSERT_EQ(demod.size(), dataInt.size() - 1);

	EXPECT_EQ(demod[0], (std::arg(std::complex<int>(5, 4) * std::conj(std::complex<int>(1, 2)))));
	EXPECT_EQ(demod[1], (std::arg(std::complex<int>(7, 9) * std::conj(std::complex<int>(5, 4)))));
	EXPECT_EQ(demod[2], (std::arg(std::complex<int>(6, 0) * std::conj(std::complex<int>(7, 9)))));

	DemodulatorFM<float> demodF;
	auto demodFl = demodF.demodulate(dataFloat);
	ASSERT_EQ(demod.size(), dataInt.size() - 1);

	EXPECT_FLOAT_EQ(demodFl[0], (std::arg(std::complex<float>(2.3f, 4.1f) * std::conj(std::complex<float>(1.1f, 0.2f)))));
	EXPECT_FLOAT_EQ(demodFl[1], (std::arg(std::complex<float>(6.9f, 4.5f) * std::conj(std::complex<float>(2.3f, 4.1f)))));
}
TEST_F(DemodulatorTest, DiffPhase) {
	std::vector<std::complex<float>> signal = {
		{1.0f, 0.0f}, 
		{0.0f, 1.0f}   
	};

	DemodulatorFM<float> demod;
	auto result = demod.demodulate(signal);

	EXPECT_FLOAT_EQ(result[0],PI/2);
}
