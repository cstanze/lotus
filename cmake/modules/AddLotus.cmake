#
# add_lotus_binary(
# 	name
#  	source1 [source2 source3 ...]
#	)
#
# name
# 	Name for new Lotus binary
#
# sources...
#		Sources for the binary
#
function(add_lotus_binary name)
	cmake_parse_arguments(ALB "" "" "" ${ARGN})

	set(ALB_SOURCES ${ALB_UNPARSED_ARGUMENTS})

	get_filename_component(base_dir ${CMAKE_CURRENT_SOURCE_DIR} NAME)

	file(GLOB_RECURSE ALB_HEADERS
      ${PROJECT_SOURCE_DIR}/include/${base_dir}/*.h
      ${PROJECT_SOURCE_DIR}/include/*.h)

	add_executable(${name} ${ALB_SOURCES} ${ALB_HEADERS})

	target_include_directories(${name}
		PUBLIC ${PROJECT_SOURCE_DIR}/include/
		# Disable it for now for Sublime's compile_commands.json DB
		# PUBLIC ${PROJECT_SOURCE_DIR}/include/${base_dir}
	)

	set_target_properties(${name}
		PROPERTIES
		OUTPUT_NAME ${name}
		LINK_FLAGS ""
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
		INSTALL_RPATH_USE_LINK_PATH TRUE
	)

	install(TARGETS ${name}
		RUNTIME
		  DESTINATION bin
		  COMPONENT Binaries
	)

	add_custom_command(
		TARGET ${name}
		POST_BUILD
		COMMAND cp ${CMAKE_BINARY_DIR}/compile_commands.json ${PROJECT_SOURCE_DIR}
		VERBATIM
	)
endfunction()
