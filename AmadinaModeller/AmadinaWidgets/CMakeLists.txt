cmake_minimum_required(VERSION 3.23)

project(${SUB_PROJECT_AMADINA_WIDGETS})

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT (CMAKE_GENERATOR MATCHES "Visual Studio") )
   set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

if(WIN32)
    add_compile_definitions(${FLAGS_WX_WIDGETS_WIN32})
endif()
if(BSD)
    add_compile_options(${WX_WIDGETS_CXX_FLAGS})
	add_link_options(${WX_WIDGETS_LIBS_FLAGS})
endif()

set(SRC_PATH src)
set(INCLUDE_PATH include)

link_directories(${OUTPUT_LIB_PATH})
if(WIN32)
    link_directories(${WX_WIDGETS_LIBRARIES})
endif()
                
set(SOURCE_FILE_LIST
	${INCLUDE_PATH}/command_panel.h
	${INCLUDE_PATH}/command_autocompleter.h
    ${INCLUDE_PATH}/command_autocompleter_vec.h
	${SRC_PATH}/command_panel.cpp
    ${SRC_PATH}/command_autocompleter_vec.cpp
    ${INCLUDE_PATH}/wxTestApp.h
    ${INCLUDE_PATH}/wxTestMain.h
    ${SRC_PATH}/wxTestMain.cpp
    ${SRC_PATH}/wxTestApp.cpp)

add_library(${AMADINA_WIDGETS_OUT_NAME} SHARED ${SOURCE_FILE_LIST})

set_target_properties(${AMADINA_WIDGETS_OUT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ARCH_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_RUNTIME_PATH}
)
     
target_include_directories(${AMADINA_WIDGETS_OUT_NAME} PRIVATE ${INCLUDE_PATH})
target_include_directories(${AMADINA_WIDGETS_OUT_NAME} PRIVATE ${WX_WIDGETS_INCLUDE_DIRS})
target_include_directories(${AMADINA_WIDGETS_OUT_NAME} PRIVATE ${WX_WIDGETS_INCLUDE_SETUP_H_DIR})

if(WIN32)
    target_link_libraries(${AMADINA_WIDGETS_OUT_NAME} PRIVATE ${WX_WIDGETS_LIBS_FILES})
endif()
