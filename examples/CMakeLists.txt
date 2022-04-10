function(ct_add_example target SOURCES)
	# create the target
	add_executable(${target} ${SOURCES})

	# sourse file grouping for IDEs
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})
	
	# set the target's folder (for IDEs that support it, e.g. Visual Studio)
	set_target_properties(${target} PROPERTIES FOLDER "Examples")

	# link the target to its SFML dependencies
	target_link_libraries(${target} PRIVATE ${PROJECT_TITLE} ${GENERAL_DEPENDENCIES})
endfunction()

add_subdirectory(tic-tac-toe)
add_subdirectory(fireball)
