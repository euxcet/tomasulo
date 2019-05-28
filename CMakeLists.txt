CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

SET (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

PROJECT(tomasulo)

SET ( CORE_SOURCE
		src/core/parser.cpp
		src/core/tomasulo.cpp
		)

SET ( CORE_HEADERS
		src/core/utils.h
		src/core/defs.h
		src/core/instruction.h
		src/core/parser.h
		src/core/rs.h
		src/core/tomasulo.h
		)

FILE ( GLOB SOURCE
		)

INCLUDE_DIRECTORIES ( src )
INCLUDE_DIRECTORIES ( src/core )
INCLUDE_DIRECTORIES ( src/data )

ADD_LIBRARY ( tomasulo STATIC
	${CORE_SOURCE}
	${CORE_HEADERS}
	${SOURCE}
	)

SET ( ALL_LIBS
		tomasulo
		${CMAKE_THREAD_LIBS_INIT}
		)

SET ( CMAKE_CXX_STANDARD 11 )

SET ( CMAKE_CXX_FLAGS "-std=c++11 -O2 ${CMAKE_CXX_FLAGS}" )

ADD_EXECUTABLE ( tomasulo_exe src/main/main.cpp )

SET_TARGET_PROPERTIES ( tomasulo_exe PROPERTIES OUTPUT_NAME main )
TARGET_LINK_LIBRARIES ( tomasulo_exe ${ALL_LIBS} )

INSTALL ( TARGETS
		tomasulo_exe
		DESTINATION
		bin
		)

INSTALL ( TARGETS
		tomasulo
		DESTINATION
		lib
		)
