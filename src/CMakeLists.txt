find_package(Boost 1.46.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

add_library(testcrap STATIC Simulation.cpp GridData.cpp)
