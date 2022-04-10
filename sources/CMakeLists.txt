file(
	GLOB_RECURSE SOURCE_LIST
	"*.[hc]pp"
	"*.[hc]"
)
#list(FILTER SOURCE_LIST EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}\/[.].*\/")

add_library(${PROJECT_TITLE} STATIC ${SOURCE_LIST})

target_link_libraries(${PROJECT_TITLE} ${GENERAL_DEPENDENCIES})

# The following line is very practical:
# it will allow you to automatically add the correct include directories with "target_link_libraries"
target_include_directories(${PROJECT_TITLE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/core FILES ${SOURCE_LIST})