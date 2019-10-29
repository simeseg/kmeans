cmake_minimum_required(VERSION 3.5.1)

set (CMAKE_CXX_STANDARD 14)
project(kmeans)

find_package(PCL 1.7 REQUIRED common)

include_directories(${PCL_INCLUDE_DIRS})
add_executable(kmeans "kmeans.cpp" "kmeans.h" "main.cpp")
target_link_libraries(kmeans ${PCL_LIBRARY_DIRS} -lGL -lglfw)

