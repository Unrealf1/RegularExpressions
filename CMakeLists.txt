cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Practice1 CXX)

option(WITH_TESTS "Build with tests and run them" OFF)
option(BUILD_DOC "Build documentation" OFF)

find_package(Doxygen)
if(BUILD_DOC)
	if (DOXYGEN_FOUND)
	    set(DOXYGEN_IN Doxygen/file.in)
	    set(DOXYGEN_OUT Doxygen)

	    # request to configure the file
	    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
	    message("Doxygen build started")

	    # note the option ALL which allows to build the docs together with the application
	    add_custom_target( doc_doxygen ALL
	        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
	        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	        COMMENT "Generating API documentation with Doxygen"
	        VERBATIM )
	else (DOXYGEN_FOUND)
	    message("Doxygen need to be installed to generate the doxygen documentation")
	endif (DOXYGEN_FOUND)
endif(BUILD_DOC)


add_subdirectory("./reglib")
add_subdirectory("./Solution")

if(WITH_TESTS)
	add_subdirectory("./Tests")
endif(WITH_TESTS)
