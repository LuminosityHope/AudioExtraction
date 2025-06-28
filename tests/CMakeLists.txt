add_executable(${PROJECT_NAME}_tests
    "CMakeAudio_ReadTests.cpp"
    "CMakeAudio_WriteTests.cpp"
    "CMakeAudio_FilterTests.cpp"
    "CMakeAudio_DemodulatorTests.cpp"
    ${SOURCES} 
 )

target_include_directories(${PROJECT_NAME}_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}_tests PRIVATE
    gtest_main
    
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)