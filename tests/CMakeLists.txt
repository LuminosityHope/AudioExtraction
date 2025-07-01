add_executable(${PROJECT_NAME}_tests

    ${CMAKE_SOURCE_DIR}/tests/CMakeAudio_ReadTests.cpp
    ${CMAKE_SOURCE_DIR}/tests/CMakeAudio_WriteTests.cpp
    ${CMAKE_SOURCE_DIR}/tests/CMakeAudio_FilterTests.cpp
    ${CMAKE_SOURCE_DIR}/tests/CMakeAudio_DemodulatorTests.cpp
    ${CMAKE_SOURCE_DIR}/src/Filter.cpp
 )

target_include_directories(${PROJECT_NAME}_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE
    gtest_main

    
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)