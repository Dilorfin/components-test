cmake_minimum_required(VERSION 3.20)

project(ComponentTest CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED) # graphics audio network system window

file(GLOB src_files
	"main.cpp"
	"core/*.hpp"
	"core/*.cpp"
	"components/*.hpp"
	"components/*.cpp"
	"systems/*.hpp"
	"systems/*.cpp"
	"sfml_extentions/**/*.hpp"
	"sfml_extentions/**/*.cpp"
)

add_executable(ComponentTest ${src_files})

target_link_libraries(ComponentTest sfml-graphics) # sfml-<component>
