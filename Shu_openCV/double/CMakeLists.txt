cmake_minimum_required(VERSION 2.8)
project( Double )
find_package( OpenCV REQUIRED )
add_executable( Double double.cpp )
target_link_libraries( Double ${OpenCV_LIBS} )
