cmake_minimum_required(VERSION 3.16)
project(CMakeAudio LANGUAGES CXX)

# ��������� �����������
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(MAKE_DIRECTORY "${OUTPUT_DIR}")
file(MAKE_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


add_subdirectory("extern/googletest-1.17.0")
add_subdirectory("tests")

# ��� �������� �����
set(SOURCES
    "${CMAKE_SOURCE_DIR}/src/CMakeAudio.cpp"
    ${CMAKE_SOURCE_DIR}/src/FromInt32ToFloat.cpp
    ${CMAKE_SOURCE_DIR}/src/wav.cpp
    ${CMAKE_SOURCE_DIR}/src/Filter.cpp)

# ��� ������������ �����
set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/CMakeAudio.h
    ${CMAKE_SOURCE_DIR}/include/Demodulator.h
    ${CMAKE_SOURCE_DIR}/include/DownSample.h
    ${CMAKE_SOURCE_DIR}/include/FileManager.h
    ${CMAKE_SOURCE_DIR}/include/Filter.h
    ${CMAKE_SOURCE_DIR}/include/FromInt32ToFloat.h
    ${CMAKE_SOURCE_DIR}/include/Wav.h
)
# ����������� ������ ������
set(DATA_FILES 
    "${CMAKE_SOURCE_DIR}/data/am_sound_1.dat"
    "${CMAKE_SOURCE_DIR}/data/file1EuropaPlus_1.bin"
)

# �������� ������������ �����
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS} 
)

# ����������� ����������
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
