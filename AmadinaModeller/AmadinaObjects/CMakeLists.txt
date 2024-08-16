cmake_minimum_required(VERSION 3.23)

project(${SUB_PROJECT_AMADINA_OBJECTS_NAME})

set(SRC_PATH src/)
set(INCLUDE_PATH include/)

add_library(${AMADINA_OBJECTS_LIB_NAME} SHARED 
	${INCLUDE_PATH}abstract_canvas.h
	${INCLUDE_PATH}abstract_operation.h
	${INCLUDE_PATH}abstract_shape.h
	${INCLUDE_PATH}circle.h
	${INCLUDE_PATH}direction.h
	${INCLUDE_PATH}direction_vector.h
	${INCLUDE_PATH}line.h
	${INCLUDE_PATH}model_tree.h
	${INCLUDE_PATH}op_boolean.h
	${INCLUDE_PATH}op_extrude.h
	${INCLUDE_PATH}point.h
	${INCLUDE_PATH}sketch.h
	${SRC_PATH}abstract_operation.cpp 
	${SRC_PATH}direction.cpp 
	${SRC_PATH}direction_vector.cpp
	${SRC_PATH}point.cpp
	${SRC_PATH}line.cpp
	${SRC_PATH}circle.cpp 
	${SRC_PATH}sketch.cpp 
	${SRC_PATH}model_tree.cpp
	${SRC_PATH}op_boolean.cpp
	${SRC_PATH}op_extrude.cpp)
	
target_include_directories(amadina_objects PRIVATE ${INCLUDE_PATH})

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