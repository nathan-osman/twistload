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
    src/main.cpp
    src/mainwindow.cpp)

qt5_wrap_cpp(MOC
    src/mainwindow.h)

qt5_wrap_ui(UI
    ui/mainwindow.ui)

add_executable(twistload WIN32
    ${SRC} ${MOC} ${UI})
qt5_use_modules(twistload Widgets)

install(TARGETS twistload
    RUNTIME DESTINATION bin)
