cmake_minimum_required(VERSION 3.23)

project(${SUB_PROJECT_AMADINA_MAIN})

set(SRC_PATH src/)
set(INCLUDE_PATH include/)
set(RES_PATH resources/)
#set(AMADINA_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OBJECTS_NAME}/include)

link_directories(../AmadinaObjects/
	../${SUB_PROJECT_wxOCCT_VIEW_NAME}/
	${WX_WIDGETS_LIBS_PATH})
	
add_executable(${AMADINA_EXECUTABLE_NAME} WIN32 
	${INCLUDE_PATH}amadina_app.h
	${INCLUDE_PATH}main_frame.h
	${SRC_PATH}amadina_app.cpp
	${SRC_PATH}main_frame.cpp
	${RES_PATH}art.cpp
	${RES_PATH}art.h
	${RES_PATH}icons.h)

target_link_libraries(${AMADINA_EXECUTABLE_NAME}
	${WX_WIDGETS_LIBS_FILE_LIST}
	${AMADINA_wxOCCT_LIB_NAME}.lib)
	
target_include_directories(${AMADINA_EXECUTABLE_NAME} PRIVATE 
	${INCLUDE_PATH}
	../${SUB_PROJECT_wxOCCT_VIEW_NAME}/include
	${WX_WIDGETS_INCLUDES_PATH}
	${WX_WIDGETS_SETUP_PATH})
	
add_compile_definitions(WIN32
	WINVER=0x0400
	__WXMSW__
	_WINDOWS
	WXUSINGDLL
	wxUSE_GUI=1
	_UNICODE
	_DEBUG
	_CRT_SECURE_NO_DEPRECATE
	_CRT_NONSTDC_NO_DEPRECATE)