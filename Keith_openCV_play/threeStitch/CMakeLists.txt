cmake_minimum_required(VERSION 2.8)
project(threeVideoStitch)
find_package(OpenCV REQUIRED)
add_executable(threeVideoStitch camStitch.cpp)
target_link_libraries(threeVideoStitch ${OpenCV_LIBS})
