cmake_minimum_required(VERSION 3.23)

project(${SUB_PROJECT_AMADINA_OCCT_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT (CMAKE_GENERATOR MATCHES "Visual Studio") )
   set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(SRC_PATH src)
set(INCLUDE_PATH include)
set(AMADINA_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OBJECTS_NAME}/include)

link_directories(../AmadinaObjects/)
link_directories(${OPENCASCADE_LIBRARIES})
link_directories(${OUTPUT_LIB_PATH})

set(SOURCE_FILE_LIST
	${INCLUDE_PATH}/circle_occt.h
	${INCLUDE_PATH}/circle_occt.h
	${INCLUDE_PATH}/line_occt.h
	${INCLUDE_PATH}/occt_canvas.h
	${INCLUDE_PATH}/occt_object.h
	${INCLUDE_PATH}/op_bool_common_occt.h
	${INCLUDE_PATH}/op_bool_fuse_occt.h
	${INCLUDE_PATH}/op_bool_occt.h
	${INCLUDE_PATH}/op_extrude_occt.h
	${INCLUDE_PATH}/point_occt.h
	${INCLUDE_PATH}/sketch_occt.h
	${SRC_PATH}/circle_occt.cpp
	${SRC_PATH}/line_occt.cpp
	${SRC_PATH}/op_bool_common_occt.cpp
	${SRC_PATH}/op_bool_fuse_occt.cpp
	${SRC_PATH}/op_bool_occt.cpp
	${SRC_PATH}/op_extrude_occt.cpp
	${SRC_PATH}/point_occt.cpp
	${SRC_PATH}/sketch_occt.cpp)
		
add_library(${AMADINA_OCCT_OUT_NAME} SHARED ${SOURCE_FILE_LIST})

set_target_properties(${AMADINA_OCCT_OUT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ARCH_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_RUNTIME_PATH}
)

target_include_directories(${AMADINA_OCCT_OUT_NAME} PRIVATE ${INCLUDE_PATH})
target_include_directories(${AMADINA_OCCT_OUT_NAME} PRIVATE ${AMADINA_OBJECTS_INCLUDE_PATH})
target_include_directories(${AMADINA_OCCT_OUT_NAME} PRIVATE ${OPENCASCADE_INCLUDE_DIRS})

target_link_libraries(${AMADINA_OCCT_OUT_NAME} PRIVATE ${AMADINA_OBJECTS_OUT_NAME})
target_link_libraries(${AMADINA_OCCT_OUT_NAME} PRIVATE ${OPENCASCADE_LIBS_FILES})

