cmake_minimum_required(VERSION 3.20)

project(ComponentTest CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED) # graphics audio network system window
find_package(box2d REQUIRED)

# TODO: add DEBUG macro definition
file(
	GLOB_RECURSE _source_list 
	"*.[hc]pp"
	"*.[hc]"
)

list(FILTER _source_list EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}\/[.].*\/")

add_executable(ComponentTest ${_source_list})

target_link_libraries(ComponentTest box2d::box2d sfml-system sfml-window sfml-graphics) # sfml-<component>

# at least it makes more nice visual studio solution and seems to not affect ninja&clang on windows
set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")
foreach(_source IN ITEMS ${_source_list})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()