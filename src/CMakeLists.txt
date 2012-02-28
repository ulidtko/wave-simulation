include_directories(.
    ${Boost_INCLUDE_DIRS}
    ${QT_INCLUDES}
    ${EIGEN3_INCLUDE_DIR}
)

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

add_library(core STATIC
    Simulation.cpp
    GridData.cpp
    rendering/MeshRenderer.cpp
)

add_subdirectory(qtgui)
