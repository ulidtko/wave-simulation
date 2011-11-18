include_directories(. ${Boost_INCLUDE_DIRS} ${Qt4_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "-std=c++0x -Wall")

add_library(testcrap STATIC
    Simulation.cpp
    GridData.cpp
    rendering/MeshRenderer.cpp
)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

QT4_WRAP_CPP(qtgui_MOC qtgui/MainWindow.h)
QT4_WRAP_UI(qtgui_FORMS qtgui/MainWindow.ui)
include_directories(${CMAKE_CURRENT_BINARY_DIR}) #-- a workaround for generated headers

add_executable(gui
    qtgui/main.cpp
    qtgui/MainWindow.cpp
    ${qtgui_MOC}
    ${qtgui_FORMS}
)

target_link_libraries(gui ${QT_LIBRARIES})
