cmake_minimum_required(VERSION 2.8)
project(openDisplayImg)
find_package(OpenCV REQUIRED)
add_executable(openDisplayImg openDisplayImg.cpp)
target_link_libraries(openDisplayImg ${OpenCV_LIBS})
