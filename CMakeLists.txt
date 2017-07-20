cmake_minimum_required(VERSION 3.2.0)
project(twistload)

set(PROJECT_NAME   "TwistLoad")
set(PROJECT_AUTHOR "Nathan Osman")

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})

find_package(Qt5Network 5.4 REQUIRED)
find_package(Qt5Widgets 5.4 REQUIRED)

set(CMAKE_AUTOMOC ON)

add_subdirectory(src)
