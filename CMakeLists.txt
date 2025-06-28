cmake_minimum_required(VERSION 3.16)
project(CMakeAudio LANGUAGES CXX)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Для всех платформ устанавливаем единую выходную директорию
file(MAKE_DIRECTORY "${OUTPUT_DIR}")
file(MAKE_DIRECTORY "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


add_subdirectory("extern/googletest-1.17.0")
add_subdirectory("tests")

# Все исходные файлы
set(SOURCES
    "src/CMakeAudio.cpp"  # Главный файл с main()
    "src/FromInt32ToFloat.cpp"
    "src/wav.cpp"
)

# Все заголовочные файлы
set(HEADERS
    "include/CMakeAudio.h"
)
# Копирование файлов данных
set(DATA_FILES 
    "data/am_sound_1.dat"
    "data/file1EuropaPlus_1.bin"
)
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
# Создание исполняемого файла
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS} 
)

# Подключение заголовков
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
