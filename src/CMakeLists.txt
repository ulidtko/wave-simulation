include_directories(.
    ${Boost_INCLUDE_DIRS}
    ${QT_INCLUDES}
    ${EIGEN3_INCLUDE_DIR}
    ${EIGEN3_INCLUDE_DIR}/unsupported
    ${UMFPACK_INCLUDES}
)

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

add_definitions(-DEIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET)

add_library(core STATIC
    Simulation.cpp
    GridData.cpp
    rendering/MeshRenderer.cpp
)

target_link_libraries(core
    ${UMFPACK_LIBRARIES}
)

add_subdirectory(qtgui)
