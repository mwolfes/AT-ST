message("\n--> Configuring tools:")

set(INCLUDE_DIRECTORIES ${ROOT_INCLUDE_DIR} ${PLUTO_INCLUDE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../lib"  )
set(LINK_DIRECTORIES  ${ROOT_LIBRARY_DIR} ${PLUTO_LIBRARY_PATH} )


include_directories( ${INCLUDE_DIRECTORIES} ) 
link_directories(${LINK_DIRECTORIES})


AUX_SOURCE_DIRECTORY("." SRCS)

############### build ################################


FOREACH (SRC ${SRCS})
	get_filename_component(f ${SRC} NAME_WE)
	add_executable(${f} ${SRC})
	target_link_libraries(${f} ${ROOT_LIBRARIES} Pluto ape )
	message("     Added binary " ${f})
ENDFOREACH(SRC)

file(GLOB PYTHON_SCRIPTS "./*.py")
FOREACH (PY ${PYTHON_SCRIPTS})
	get_filename_component(py_file ${PY} NAME_WE)
	add_custom_target(python_${py_file} ALL
		COMMAND ${CMAKE_COMMAND} -E create_symlink "${PY}" "${EXECUTABLE_OUTPUT_PATH}/${py_file}"
		COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_CURRENT_SOURCE_DIR}/../lib/pylib" "${EXECUTABLE_OUTPUT_PATH}/../lib/pylib"
		)
ENDFOREACH(PY)

message("\n")


