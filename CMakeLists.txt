cmake_minimum_required(VERSION 3.16)
project(CMakeAudio LANGUAGES CXX)

# Íàñòðîéêè êîìïèëÿòîðà
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

# Âñå èñõîäíûå ôàéëû
set(SOURCES
    "src/CMakeAudio.cpp"  # Ãëàâíûé ôàéë ñ main()
    "src/FromInt32ToFloat.cpp"
    "src/wav.cpp"
)

# Âñå çàãîëîâî÷íûå ôàéëû
set(HEADERS
    "include/CMakeAudio.h"
    "include/Demodulator.h"
    "include/DownSample.h"
    "include/FileManager.h"
    "include/Filter.h"
    "include/FromInt32ToFloat.h"
    "include/Wav.h"
)
# Êîïèðîâàíèå ôàéëîâ äàííûõ
set(DATA_FILES 
    "data/am_sound_1.dat"
    "data/file1EuropaPlus_1.bin"
)
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
# Ñîçäàíèå èñïîëíÿåìîãî ôàéëà
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS} 
)

# Ïîäêëþ÷åíèå çàãîëîâêîâ
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
