cmake_minimum_required(VERSION 2.6)

project("Wave simulation" CXX C)
find_package(Boost 1.46.0 REQUIRED)
find_package(Qt4 REQUIRED)
add_subdirectory(src)
