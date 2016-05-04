cmake_minimum_required(VERSION 3.5)
project(Join_Robockets_Clientside)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp clicker.cpp)

set(OPENCV_LIBS opencv_core opencv_highgui opencv_imgcodecs opencv_imgproc opencv_videoio)
set(XLIB_LIBS X11)
set(LIBS ${OPENCV_LIBS} ${XLIB_LIBS})

add_executable(Join_Robockets_Clientside ${SOURCE_FILES})
target_link_libraries(Join_Robockets_Clientside ${LIBS})
