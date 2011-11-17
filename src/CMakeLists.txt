include_directories(. ${Boost_INCLUDE_DIRS} ${Qt4_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

add_library(testcrap STATIC
    Simulation.cpp
    GridData.cpp
    render/MeshRenderer.cpp
)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

add_executable(qtgui
    qtgui/main.cpp
)

target_link_libraries(qtgui ${QT_LIBRARIES})
