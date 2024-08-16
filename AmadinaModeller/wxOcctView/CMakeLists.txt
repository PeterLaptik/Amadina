cmake_minimum_required(VERSION 3.23)

project(${SUB_PROJECT_wxOCCT_VIEW_NAME})

set(SRC_PATH src/)
set(INCLUDE_PATH include/)
set(AMADINA_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OBJECTS_NAME}/include)
set(AMADINA_OCCT_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OCCT_NAME}/include)

link_directories(../AmadinaObjects/ 
	../AmadinaOCCT/
	../wxOcctView/
	${WX_WIDGETS_LIBS_PATH}
	${OPENCASCADE_PATH_LIBS})

add_library(${AMADINA_wxOCCT_LIB_NAME} SHARED 
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
		
include_directories(${AMADINA_wxOCCT_LIB_NAME} PRIVATE 
	${INCLUDE_PATH} 
	${OPENCASCADE_PATH_INCLUDE}
	${AMADINA_OBJECTS_INCLUDE_PATH}
	${AMADINA_OCCT_OBJECTS_INCLUDE_PATH}
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

target_link_libraries(${AMADINA_wxOCCT_LIB_NAME} 
	${AMADINA_OBJECTS_LIB_NAME}.lib
	${AMADINA_OCCT_LIB_NAME}.lib
	${OCCT_LIBS_FILE_LIST}
	${WX_WIDGETS_LIBS_FILE_LIST})
