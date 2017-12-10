cmake_minimum_required(VERSION 2.8)

set(project_name bserver)
set(project_src
	src/bserver.cpp
	src/Server.cpp
	src/ServerThread.cpp
)

project(${project_name})
add_executable(${project_name} ${project_src})
set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 11)
qt5_use_modules(${project_name} ${qt_modules})
add_definitions(${blind_DEFINITIONS})
include_directories(${blind_INCLUDE_DIRS})
target_link_libraries(${project_name} blind)
