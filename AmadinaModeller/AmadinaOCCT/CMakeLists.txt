cmake_minimum_required(VERSION 3.23)

project(${SUB_PROJECT_AMADINA_OCCT_NAME})

set(SRC_PATH src/)
set(INCLUDE_PATH include/)
set(AMADINA_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OBJECTS_NAME}/include)

link_directories(../AmadinaObjects/
	${OPENCASCADE_PATH_LIBS})

add_library(${AMADINA_OCCT_LIB_NAME} SHARED 
	${INCLUDE_PATH}circle_occt.h
	${INCLUDE_PATH}circle_occt.h
	${INCLUDE_PATH}line_occt.h
	${INCLUDE_PATH}occt_canvas.h
	${INCLUDE_PATH}occt_object.h
	${INCLUDE_PATH}op_bool_common_occt.h
	${INCLUDE_PATH}op_bool_fuse_occt.h
	${INCLUDE_PATH}op_bool_occt.h
	${INCLUDE_PATH}op_extrude_occt.h
	${INCLUDE_PATH}point_occt.h
	${INCLUDE_PATH}sketch_occt.h
	${SRC_PATH}circle_occt.cpp
	${SRC_PATH}line_occt.cpp
	${SRC_PATH}op_bool_common_occt.cpp
	${SRC_PATH}op_bool_fuse_occt.cpp
	${SRC_PATH}op_bool_occt.cpp
	${SRC_PATH}op_extrude_occt.cpp
	${SRC_PATH}point_occt.cpp
	${SRC_PATH}sketch_occt.cpp)
		
target_include_directories(${AMADINA_OCCT_LIB_NAME} PRIVATE ${INCLUDE_PATH})
include_directories(${AMADINA_OCCT_LIB_NAME} PRIVATE ${AMADINA_OBJECTS_INCLUDE_PATH} ${OPENCASCADE_PATH_INCLUDE})

target_link_libraries(${AMADINA_OCCT_LIB_NAME} 
	${AMADINA_OBJECTS_LIB_NAME}.lib
	${OCCT_LIBS_FILE_LIST})

