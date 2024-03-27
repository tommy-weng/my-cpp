cmake_minimum_required (VERSION 2.8)

project (demo)

# get_filename_component(CURRENT_FOLDER ${CURRENT_FOLDER_ABSOLUTE} NAME)
include_directories(..)

link_libraries(gtest_main gtest gmock pthread)

add_executable(output TestTranscript.cpp)