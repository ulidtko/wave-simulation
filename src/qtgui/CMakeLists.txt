include(${QT_USE_FILE})

QT4_WRAP_CPP(qtgui_MOC
    MainWindow.h
    MyGLWidget.h
)
QT4_WRAP_UI(qtgui_FORMS MainWindow.ui)
include_directories(. ${CMAKE_CURRENT_BINARY_DIR}) #-- a workaround for generated headers

QT4_ADD_RESOURCES(qtgui_RCC main.qrc)

add_executable(qtgui
    main.cpp
    MainWindow.cpp
    MyGLWidget.cpp
    ${qtgui_MOC}
    ${qtgui_FORMS}
    ${qtgui_RCC}
)

target_link_libraries(qtgui
    core
    ${QT_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
