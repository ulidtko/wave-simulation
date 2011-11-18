include_directories(. ${Boost_INCLUDE_DIRS} ${QT_INCLUDES})

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

add_library(testcrap STATIC
    Simulation.cpp
    GridData.cpp
    rendering/MeshRenderer.cpp
)

add_subdirectory(qtgui)
