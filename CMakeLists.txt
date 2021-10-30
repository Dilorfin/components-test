cmake_minimum_required(VERSION 3.20)

project(ComponentTest CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED) # graphics audio network system window
find_package(box2d REQUIRED)

file(GLOB src_files
	"main.cpp"
	"core/*.[hc]pp"
	"components/*.[hc]pp"
	"systems/*.[hc]pp"
	"objects/*.[hc]pp"
	"physics/*.[hc]pp"
	"sfml_extentions/**/*.[hc]pp"
)

add_executable(ComponentTest ${src_files})

target_link_libraries(ComponentTest box2d::box2d sfml-graphics) # sfml-<component>
