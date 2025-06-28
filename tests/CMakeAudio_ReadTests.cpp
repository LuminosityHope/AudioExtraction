#include "gtest/gtest.h"
#include "CMakeAudio.h" 
#include <fstream>
#include <filesystem>

template<typename T>
void CreateTestFile(const std::string& filename, const std::vector<T>& data) {
    std::ofstream file(filename, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(T));
}

class ReadSignalTest : public ::testing::Test {
protected:
    virtual void SetUp(void)  {
    
        std::vector<float> good_data = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
        CreateTestFile("good_file.bin", good_data);

        std::vector<float> bad_data = { 1.0f, 2.0f, 3.0f }; 
        CreateTestFile("bad_file.bin", bad_data);
    }

   virtual void TearDown(void)  {
        
        std::filesystem::remove("good_file.bin");
        std::filesystem::remove("bad_file.bin");
    }
};

 
TEST_F(ReadSignalTest, ReadsFileCorrectly) {
    auto result = FileManager::ReadSignal<float>("good_file.bin");

    ASSERT_EQ(result.size(), 3);
    EXPECT_FLOAT_EQ(result[0].real(), 1.0f);
    EXPECT_FLOAT_EQ(result[0].imag(), 2.0f);
    EXPECT_FLOAT_EQ(result[1].real(), 3.0f);
    EXPECT_FLOAT_EQ(result[1].imag(), 4.0f);
    EXPECT_FLOAT_EQ(result[2].real(), 5.0f);
    EXPECT_FLOAT_EQ(result[2].imag(), 6.0f);
}


TEST_F(ReadSignalTest, ThrowsOnNonexistentFile) {
    EXPECT_THROW({
         FileManager::ReadSignal<float>("nonexistent_file.bin");
        }, std::runtime_error);
}

TEST_F(ReadSignalTest, ThrowsOnOddSize) {
    EXPECT_THROW({
         FileManager::ReadSignal<float>("bad_file.bin");
        }, std::runtime_error);
}
