cmake_minimum_required(VERSION 3.25)

project(${SUB_PROJECT_AMADINA_WX_OCCT_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT (CMAKE_GENERATOR MATCHES "Visual Studio") )
   set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_compile_definitions(${wxWidgets_DEFINITIONS})

set(SRC_PATH src)
set(INCLUDE_PATH include)
set(AMADINA_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OBJECTS_NAME}/include)
set(AMADINA_OCCT_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OCCT_NAME}/include)
set(AMADINA_OCCT_PANEL_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_WX_OCCT_PANEL_NAME}/include)

link_directories(${OUTPUT_LIB_PATH})
link_directories(${OpenCASCADE_LIBRARY_DIR})
link_directories(${wxWidgets_LIBRARY_DIR})

set(SOURCE_FILE_LIST
	${INCLUDE_PATH}/abstract_modeller.h
	${INCLUDE_PATH}/context.h
	${INCLUDE_PATH}/factory.h
	${INCLUDE_PATH}/menu_htree.h
	${INCLUDE_PATH}/objectpool.h
	${INCLUDE_PATH}/resource_provider.h
	${INCLUDE_PATH}/screen_modes.h
	${INCLUDE_PATH}/wxmodeller3d.h
	${INCLUDE_PATH}/wxmodeltree.h
	${INCLUDE_PATH}/wxoccpanel.h
	${INCLUDE_PATH}/wxoccpanel_styles.h
	${SRC_PATH}/context.cpp
	${SRC_PATH}/factory.cpp
	${SRC_PATH}/menu_htree.cpp
	${SRC_PATH}/objectpool.cpp
	${SRC_PATH}/wxmodeller3d.cpp
	${SRC_PATH}/wxmodeltree.cpp
	${SRC_PATH}/wxoccpanel.cpp
	${SRC_PATH}/wxoccpanel_styles.cpp)
		
add_library(${AMADINA_WX_OCCT_OUT_NAME} SHARED ${SOURCE_FILE_LIST})

set_target_properties(${AMADINA_WX_OCCT_OUT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ARCH_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_RUNTIME_PATH}
)

target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${INCLUDE_PATH})
target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${AMADINA_OBJECTS_INCLUDE_PATH})
target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${AMADINA_OCCT_OBJECTS_INCLUDE_PATH})
target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${AMADINA_OCCT_PANEL_INCLUDE_PATH})
target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${OpenCASCADE_INCLUDE_DIR})
target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${X11_INCLUDE_DIR})

if(BSD)
	target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${GTK3_INCLUDE_DIRS})
	#target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${GLIB_INCLUDE_DIRS})
	#target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${PANGO_INCLUDE_DIRS})
	#target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${GDK_PIX_BUF_INCLUDE_DIRS})
	#target_include_directories(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${ATK_INCLUDE_DIRS})
endif()

target_link_libraries(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${AMADINA_OCCT_OUT_NAME})
target_link_libraries(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${AMADINA_OBJECTS_OUT_NAME})
target_link_libraries(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${OpenCASCADE_LIBRARIES})
target_link_libraries(${AMADINA_WX_OCCT_OUT_NAME} PRIVATE ${wxWidgets_LIBRARIES})
