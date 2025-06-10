cmake_minimum_required(VERSION 3.25)

project(${SUB_PROJECT_AMADINA_WIDGETS_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT (CMAKE_GENERATOR MATCHES "Visual Studio") )
   set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_compile_definitions(${wxWidgets_DEFINITIONS})

set(SRC_PATH src)
set(INCLUDE_PATH include)

link_directories(${OUTPUT_LIB_PATH})
link_directories(${wxWidgets_LIBRARY_DIR})
          
set(SOURCE_FILE_LIST
	${INCLUDE_PATH}/command_panel.h
	${INCLUDE_PATH}/command_autocompleter.h
	${SRC_PATH}/command_panel.cpp
    ${SRC_PATH}/command_autocompleter.cpp
    #${INCLUDE_PATH}/wxTestApp.h
    #${INCLUDE_PATH}/wxTestMain.h
    #${SRC_PATH}/wxTestMain.cpp
    #${SRC_PATH}/wxTestApp.cpp
	)

add_library(${AMADINA_WIDGETS_OUT_NAME} SHARED ${SOURCE_FILE_LIST})

set_target_properties(${AMADINA_WIDGETS_OUT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ARCH_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_RUNTIME_PATH}
)
     
target_include_directories(${AMADINA_WIDGETS_OUT_NAME} PRIVATE ${INCLUDE_PATH})
target_include_directories(${AMADINA_WIDGETS_OUT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_link_libraries(${AMADINA_WIDGETS_OUT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

