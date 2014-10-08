include_directories(.
    ${Boost_INCLUDE_DIRS}
    ${QT_INCLUDES}
    ${EIGEN3_INCLUDE_DIR}
    ${UMFPACK_INCLUDES}
)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_library(core STATIC
    simulation/Simulation.cpp
    simulation/GridData.cpp
    simulation/Perturbator.cpp
    simulation/InteractionController.cpp
    rendering/MeshRenderer.cpp
    rendering/ImageRenderer.cpp
)

target_link_libraries(core
    ${UMFPACK_LIBRARIES}
)

add_subdirectory(qtgui)
