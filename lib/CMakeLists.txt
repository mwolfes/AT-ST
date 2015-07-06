message("\n--> Configuring ape libraries:")

set(INCLUDE_DIRECTORIES ${ROOT_INCLUDE_DIR} ${PLUTO_INCLUDE_PATH} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )
set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR} ${PLUTO_LIBRARY_PATH} )


include_directories( ${INCLUDE_DIRECTORIES} )
link_directories( ${LINK_DIRECTORIES})

ADD_CUSTOM_COMMAND(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/chgen.h
	COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/DecayParser.py ${CMAKE_CURRENT_SOURCE_DIR}/xsections.dat ${CMAKE_CURRENT_BINARY_DIR}/chgen.h
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/xsections.dat ${CMAKE_CURRENT_SOURCE_DIR}/DecayParser.py
)


AUX_SOURCE_DIRECTORY("." SRCS)
add_library(ape SHARED ${SRCS} ${CMAKE_CURRENT_BINARY_DIR}/chgen.h)
target_link_libraries( ape ${ROOT_LIBRARIES} MathMore)

FOREACH (SRC ${SRCS})
	get_filename_component( f ${SRC} NAME_WE )
	message("     Added ${f} to ape library")
ENDFOREACH(SRC)
