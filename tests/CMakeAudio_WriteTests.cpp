#include "gtest/gtest.h"
#include "CMakeAudio.h" 
#include <fstream>
#include <filesystem>

class SaveSignalTest : public ::testing::Test {
protected:
    void TearDown() override {
        std::filesystem::remove("test.bin");
    }
};

TEST_F(SaveSignalTest, WritesFileCorrectly) {
    std::vector<float> data = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
    const std::string filename = "test.bin";

    ASSERT_NO_THROW(FileManager::SaveSignal(data, filename));

    // Проверяем, что файл создан и имеет правильный размер
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    ASSERT_TRUE(file.is_open());
    EXPECT_EQ(file.tellg(), data.size() * sizeof(float));
}
TEST_F(SaveSignalTest, DifferentTypes)
{
    const std::string filename = "test.bin";
    std::vector<int> intData = { 1,2,3,4,5 };
    ASSERT_NO_THROW(FileManager::SaveSignal(intData, filename));

    std::vector<double> doubleData = { 1.1, 2.4 ,3.3 ,4.8 ,5.1 };
    ASSERT_NO_THROW(FileManager::SaveSignal(doubleData, filename));
}
TEST_F(SaveSignalTest, DataCorrectly)
{
    std::vector<float> data = { 1.1f, 2.1f, 3.1f, 4.1f, 5.1f, 6.1f };
    const std::string filename = "test.bin";
    ASSERT_NO_THROW(FileManager::SaveSignal(data, filename));
    std::ifstream file(filename, std::ios::binary);
    std::vector<float> readData(data.size()*sizeof(float));
    file.read(reinterpret_cast<char*>(readData.data()), data.size() * sizeof(float));
    for (size_t i = 0; i < data.size(); ++i) {
        EXPECT_FLOAT_EQ(readData[i], data[i]);
      
    }

}