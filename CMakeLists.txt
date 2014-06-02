cmake_minimum_required(VERSION 2.8.9)
project(twistload)

find_package(Qt5Widgets)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

configure_file(src/config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set(SRC
    src/aboutdialog.cpp
    src/main.cpp
    src/mainwindow.cpp)

qt5_wrap_cpp(MOC
    src/aboutdialog.h
    src/mainwindow.h)

qt5_wrap_ui(UI
    ui/aboutdialog.ui
    ui/mainwindow.ui)

qt5_add_resources(QRC resources.qrc)

add_executable(twistload WIN32 ${SRC} ${MOC} ${UI} ${QRC})
qt5_use_modules(twistload Widgets)

install(TARGETS twistload
    RUNTIME DESTINATION bin)
