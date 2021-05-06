cmake_minimum_required(VERSION 2.8.4)
project(hiddenwave)

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp headers/main.h Algorithm.cpp headers/Algorithm.h CustomHeader.cpp headers/CustomHeader.h)
add_executable(hiddenwave ${SOURCE_FILES})
TARGET_LINK_LIBRARIES( hiddenwave ${Boost_LIBRARIES} )
