cmake_minimum_required(VERSION 2.8)
project(twoVideoStitch)
find_package(OpenCV REQUIRED)
add_executable(twoVideoStitch camStitch.cpp)
target_link_libraries(twoVideoStitch ${OpenCV_LIBS})
