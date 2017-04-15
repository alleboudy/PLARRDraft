cmake_minimum_required(VERSION 2.8) 
PROJECT (pilotTest)
MESSAGE("aaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa")
MESSAGE("$ENV{OpenCV_DIR}")

find_package(OpenCV REQUIRED )

set( NAME_SRC
    src/main.cpp    
)

set( NAME_HEADERS       
     include/header.h
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
include_directories( ${OpenCV_INCLUDE_DIRS} )

link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
add_executable( pilotTest ${NAME_SRC} ${NAME_HEADERS} )
MESSAGE("aaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa")
MESSAGE(${OpenCV_INCLUDE_DIRS})
MESSAGE("$ENV{OpenCV_LIBS}")
set(OpenCV_LIBS "opencv_world")
MESSAGE("${OpenCV_LIBS}")

MESSAGE("aaAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaa")

target_link_libraries( pilotTest $ENV{OpenCV_LIBS}/opencv_world320d.lib )