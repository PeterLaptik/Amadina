cmake_minimum_required(VERSION 3.0)

set(VERSION "0.1")
project(Amadina VERSION ${VERSION})


# wxWidgets library paths
set(WX_WIDGETS_SETUP 	"" 	CACHE PATH "Path to wxWidgets-library setup.h file")
set(WX_WIDGETS_INCLUDE 	"" 	CACHE PATH "Path to wxWidgets-library include files")
set(WX_WIDGETS_LIB 		"" 	CACHE PATH "Path to wxWidgets-library .lib/.a and .dll files")


set(CMAKE_CXX_STANDARD 11)


# Check wxWidgets settings
if(WIN32)
	if(WX_WIDGETS_INCLUDE STREQUAL "")
		message(SEND_ERROR "Error: enter 'WX_WIDGETS_INCLUDE' - Path to wxWidgets-library include files")
	endif()

	if(WX_WIDGETS_LIB STREQUAL "")
		message(SEND_ERROR "Error: enter 'WX_WIDGETS_INCLUDE' - Path to wxWidgets-library .lib/.a and .dll files")
	endif()

	if(WX_WIDGETS_SETUP STREQUAL "")
		message(SEND_ERROR "Error: enter 'WX_WIDGETS_INCLUDE' - Path to wxWidgets-library setup.h file")
	endif()
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_subdirectory(amadina)
add_subdirectory(wx_binding)
add_subdirectory(kernel)


