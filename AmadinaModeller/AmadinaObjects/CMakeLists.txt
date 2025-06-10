cmake_minimum_required(VERSION 3.25)

project(${SUB_PROJECT_AMADINA_OBJECTS_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT (CMAKE_GENERATOR MATCHES "Visual Studio") )
   set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(SRC_PATH src)
set(INCLUDE_PATH include)

set(SOURCE_FILE_LIST 
	${INCLUDE_PATH}/abstract_canvas.h
	${INCLUDE_PATH}/abstract_operation.h
	${INCLUDE_PATH}/abstract_shape.h
	${INCLUDE_PATH}/circle.h
	${INCLUDE_PATH}/direction.h
	${INCLUDE_PATH}/direction_vector.h
	${INCLUDE_PATH}/line.h
	${INCLUDE_PATH}/model_tree.h
	${INCLUDE_PATH}/op_boolean.h
	${INCLUDE_PATH}/op_extrude.h
	${INCLUDE_PATH}/point.h
	${INCLUDE_PATH}/sketch.h
	${SRC_PATH}/abstract_operation.cpp 
	${SRC_PATH}/direction.cpp 
	${SRC_PATH}/direction_vector.cpp
	${SRC_PATH}/point.cpp
	${SRC_PATH}/line.cpp
	${SRC_PATH}/circle.cpp 
	${SRC_PATH}/sketch.cpp 
	${SRC_PATH}/model_tree.cpp
	${SRC_PATH}/op_boolean.cpp
	${SRC_PATH}/op_extrude.cpp)

add_library(${AMADINA_OBJECTS_OUT_NAME} SHARED ${SOURCE_FILE_LIST})

set_target_properties(${AMADINA_OBJECTS_OUT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ARCH_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_RUNTIME_PATH}
)

target_include_directories(${AMADINA_OBJECTS_OUT_NAME} PRIVATE ${INCLUDE_PATH})