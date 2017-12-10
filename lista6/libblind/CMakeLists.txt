cmake_minimum_required(VERSION 2.8)

set(project_name blind)
set(project_src
	src/libblind.cpp
)

project(${project_name})
add_library(${project_name} SHARED ${project_src})
set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 11)
qt5_use_modules(${project_name} Core)
set(${project_name}_DEFINITIONS CACHE INTERNAL "${project_name}: Definitions" FORCE)
set(${project_name}_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include
    CACHE INTERNAL "${project_name}: Include Directories" FORCE)
