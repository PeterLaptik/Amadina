cmake_minimum_required(VERSION 3.23)

project(${SUB_PROJECT_AMADINA_WX_OCCT_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT (CMAKE_GENERATOR MATCHES "Visual Studio") )
   set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(SRC_PATH src/)
set(INCLUDE_PATH include/)
set(AMADINA_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OBJECTS_NAME}/include)
set(AMADINA_OCCT_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OCCT_NAME}/include)

link_directories(${OUTPUT_LIB_PATH}
                ${WX_WIDGETS_LIBS_PATH}
                ${OPENCASCADE_LIBS_PATH})

set(SOURCE_FILE_LIST
	${INCLUDE_PATH}abstract_modeller.h
	${INCLUDE_PATH}context.h
	${INCLUDE_PATH}factory.h
	${INCLUDE_PATH}menu_htree.h
	${INCLUDE_PATH}objectpool.h
	${INCLUDE_PATH}resource_provider.h
	${INCLUDE_PATH}screen_modes.h
	${INCLUDE_PATH}wxmodeller3d.h
	${INCLUDE_PATH}wxmodeltree.h
	${INCLUDE_PATH}wxoccpanel.h
	${INCLUDE_PATH}wxoccpanel_styles.h
	${SRC_PATH}context.cpp
	${SRC_PATH}factory.cpp
	${SRC_PATH}menu_htree.cpp
	${SRC_PATH}objectpool.cpp
	${SRC_PATH}wxmodeller3d.cpp
	${SRC_PATH}wxmodeltree.cpp
	${SRC_PATH}wxoccpanel.cpp
	${SRC_PATH}wxoccpanel_styles.cpp)
		
add_library(${AMADINA_WX_OCCT_OUT_NAME} SHARED ${SOURCE_FILE_LIST})

set_target_properties(${AMADINA_WX_OCCT_OUT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ARCH_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_RUNTIME_PATH}
)

target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE 
	${INCLUDE_PATH}
    ${AMADINA_OBJECTS_INCLUDE_PATH}
	${AMADINA_OCCT_OBJECTS_INCLUDE_PATH}
	${OPENCASCADE_INCLUDE_PATH}
	${WX_WIDGETS_INCLUDE_PATH}
	${WX_WIDGETS_SETUP_PATH})

if(WIN32)
    add_compile_definitions(${FLAGS_WX_WIDGETS})
endif()

target_link_libraries(${AMADINA_WX_OCCT_OUT_NAME} 
	${AMADINA_OCCT_OUT_NAME} 
    ${AMADINA_OBJECTS_OUT_NAME}
	${OPENCASCADE_LIBS_FILES}
	${WX_WIDGETS_LIBS_FILES})
