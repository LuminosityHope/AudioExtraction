#include "gtest/gtest.h"
#include "CMakeAudio.h" 


class FilterTest : public ::testing::Test {
protected:
    void SetUp() override {
        testFloat = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
        testInt = { 10, 20, 30, 40, 50 };
    }
    std::vector<float> testFloat;
    std::vector<int> testInt;
};TEST_F(FilterTest,DataCorrectly)
{
    Filter filter(3, "mean");  
    auto resultFloat = filter.filtration(testFloat);
    ASSERT_EQ(resultFloat.size(), 4);
    EXPECT_FLOAT_EQ(resultFloat[0], (1.0f + 2.0f + 3.0f) / 3);
    EXPECT_FLOAT_EQ(resultFloat[1], (2.0f + 3.0f + 4.0f) / 3);
    EXPECT_FLOAT_EQ(resultFloat[2], (3.0f + 4.0f + 5.0f) / 3);
    EXPECT_FLOAT_EQ(resultFloat[3], (4.0f + 5.0f + 6.0f) / 3);

    Filter filtInt(3, "mean");
    auto resultInt = filtInt.filtration(testInt);
    ASSERT_EQ(resultInt.size(), 3);
    EXPECT_EQ(resultInt[0], (10 + 20 + 30) / 3);
    EXPECT_EQ(resultInt[1], (20 + 30 + 40) / 3);
    EXPECT_EQ(resultInt[2], (30 + 40 + 50) / 3);
}
