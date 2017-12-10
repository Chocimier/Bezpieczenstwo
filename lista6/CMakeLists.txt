cmake_minimum_required(VERSION 2.8)

find_package(Boost REQUIRED)

add_subdirectory("libblind")
add_subdirectory("bserver")
add_subdirectory("bclient")
add_subdirectory("bverify")
