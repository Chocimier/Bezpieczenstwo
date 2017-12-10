cmake_minimum_required(VERSION 2.8)

find_package(Boost REQUIRED)

set(qt_modules Core Network)
set(qt_required_version 5)
find_package(Qt5 ${qt_required_version} REQUIRED COMPONENTS ${qt_modules})
set(CMAKE_AUTOMOC ON)

add_subdirectory("libblind")
add_subdirectory("bserver")
add_subdirectory("bclient")
add_subdirectory("bverify")
