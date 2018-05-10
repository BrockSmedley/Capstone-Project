cmake_minimum_required(VERSION 2.8)
project( Latency )
find_package( OpenCV REQUIRED )
add_executable( Latency tiled_latency3.cpp )
target_link_libraries( Latency ${OpenCV_LIBS} )

