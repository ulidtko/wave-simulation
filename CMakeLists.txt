cmake_minimum_required(VERSION 2.6)

project("Wave simulation" CXX C)
find_package(Boost 1.46.0 REQUIRED)
find_package(Qt4 REQUIRED QtCore QtGui QtOpenGL)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
find_package(Eigen3 3.0.0 REQUIRED)
find_package(Umfpack)

add_subdirectory(src)
