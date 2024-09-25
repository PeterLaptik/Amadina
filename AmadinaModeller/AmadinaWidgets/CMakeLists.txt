cmake_minimum_required(VERSION 3.23)

project(AmadinaWidgets)

set(THIS__NAME test)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(WX_WIDGETS_PATH D:/CPP-repository/wxWidgets-3.0.5)
set(WX_WIDGETS_LIBS_PATH D:/CPP-repository/wxWidgets-3.0.5/lib/vc_x64d_dll)
set(WX_WIDGETS_SETUP_PATH D:/CPP-repository/wxWidgets-3.0.5/lib/vc_x64d_dll/mswud)
set(WX_WIDGETS_INCLUDE_PATH ${WX_WIDGETS_PATH}/include)

set(SRC_PATH src)
set(INCLUDE_PATH include)
set(FLAGS_WX_WIDGETS
        WINVER=0x0400
        __WXMSW__
        _WINDOWS
        WXUSINGDLL
        wxUSE_GUI=1
        _UNICODE
        _DEBUG
        _CRT_SECURE_NO_DEPRECATE
        _CRT_NONSTDC_NO_DEPRECATE)
        
add_compile_definitions(${FLAGS_WX_WIDGETS})
link_directories(${WX_WIDGETS_LIBS_PATH})

add_executable(${THIS__NAME} WIN32
	${INCLUDE_PATH}/command_panel.h
	${INCLUDE_PATH}/wxTestApp.h
	${SRC_PATH}/command_panel.cpp
	${SRC_PATH}/wxTestApp.cpp
    ${INCLUDE_PATH}/wxTestMain.h
    ${SRC_PATH}/wxTestMain.cpp)

                
target_link_libraries(${THIS__NAME}  wxbase30ud.lib;wxbase30ud_net.lib;wxbase30ud_xml.lib;wxexpatd.lib;wxjpegd.lib;wxmsw30ud_adv.lib;wxmsw30ud_aui.lib;wxmsw30ud_core.lib;wxmsw30ud_gl.lib;wxmsw30ud_html.lib;wxmsw30ud_media.lib;wxmsw30ud_propgrid.lib;wxmsw30ud_qa.lib;wxmsw30ud_ribbon.lib;wxmsw30ud_richtext.lib;wxmsw30ud_stc.lib;wxmsw30ud_webview.lib;wxmsw30ud_xrc.lib;wxpngd.lib;wxregexud.lib;wxscintillad.lib;wxtiffd.lib;wxzlibd.lib)
	
target_include_directories(${THIS__NAME} PRIVATE 
	${INCLUDE_PATH}
	${WX_WIDGETS_INCLUDE_PATH}
	${WX_WIDGETS_SETUP_PATH})