cmake_minimum_required(VERSION 3.5)
project(zcm)
set (CMAKE_CXX_FLAGS "-std=c++11")
include_directories(${zcm_SOURCE_DIR}/include)
add_subdirectory(src)
install(DIRECTORY ${zcm_SOURCE_DIR}/include/ DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")
