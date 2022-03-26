cmake_minimum_required(VERSION 3.20)

set(PROJECT_TITLE ComponentTest)

project(${PROJECT_TITLE} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(SFML 3 COMPONENTS System Window Graphics REQUIRED) # graphics audio network system window
find_package(box2d REQUIRED)
message("-- Found box2d in ${box2d_DIR}")

set(GENERAL_DEPENDENCIES box2d::box2d SFML::System SFML::Window SFML::Graphics)

file(
	GLOB_RECURSE SOURCE_LIST
	"*.[hc]pp"
	"*.[hc]"
)

list(FILTER SOURCE_LIST EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}\/[.].*\/")

add_executable(${PROJECT_TITLE} ${SOURCE_LIST})

target_link_libraries(${PROJECT_TITLE} ${GENERAL_DEPENDENCIES}) # SFML::<component>

if(BUILD_TESTS)
	find_package(doctest REQUIRED)
	message("-- Found doctest in ${doctest_DIR}")

	set(SOURCE_LIST_WO_MAIN ${SOURCE_LIST})
	list(FILTER SOURCE_LIST_WO_MAIN EXCLUDE REGEX ".*main\.cpp")

	enable_testing()
	add_subdirectory(.tests)
endif(BUILD_TESTS)

# Prettify IDEs Projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Visual Studio Startup Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_TITLE})
# sourse file grouping for IDEs
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})
