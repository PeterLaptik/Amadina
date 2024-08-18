cmake_minimum_required(VERSION 3.23)

project(AmadinaModeller)

# Sub-projects names
set(SUB_PROJECT_AMADINA_OBJECTS_NAME AmadinaObjects)
set(SUB_PROJECT_AMADINA_OCCT_NAME AmadinaOCCT)
set(SUB_PROJECT_wxOCCT_VIEW_NAME wxOcctView)
set(SUB_PROJECT_AMADINA_MAIN AmadinaModeller)

# Output file names
set(AMADINA_OBJECTS_LIB_NAME amadina_objects)
set(AMADINA_OCCT_LIB_NAME amadina_occt)
set(AMADINA_wxOCCT_LIB_NAME wxocctview)
set(AMADINA_EXECUTABLE_NAME Amadina3D)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	
# Paths to OpenCasCade library
# OPENCASCADE_PATH - path to root folder of OCCT-library destination
# OPENCASCADE_PLATFORM / OPENCASCADE_COMPILLER are used for building full path to OCCT-binaries
if(WIN32)
	SET(OPENCASCADE_PATH 
		"C:/CPP/OpenCASCADE-7.6.0-vc14-64/opencascade-7.6.0" 
		CACHE PATH "Path to OCCT-library directory")

	SET(OPENCASCADE_PLATFORM 
		"win64" 
		CACHE STRING "OCCT-library platform tag(in path %occt_root%/win64/vc14/lib/ 'win64'-value)")
		
	SET(OPENCASCADE_COMPILLER 
		"vc14" 
		CACHE STRING "OCCT-library compiller tag (in path %occt_root%/win64/vc14/lib/ 'vc14'-value)")
		
	SET(OPENCASCADE_PATH_INCLUDE ${OPENCASCADE_PATH}/inc)
	SET(OPENCASCADE_PATH_LIBS ${OPENCASCADE_PATH}/${OPENCASCADE_PLATFORM}/${OPENCASCADE_COMPILLER}/lib/)
endif(WIN32)


# Paths to wxWidgets-library
if(WIN32)
	SET(WX_WIDGETS_INCLUDES_PATH 
		"C:/Users/pyotr/Documents/c_projects/wxWidgets-3.0.5/include" 
		CACHE PATH "Path to wxWidgets-library includes directory")

	SET(WX_WIDGETS_LIBS_PATH 
		"C:/Users/pyotr/Documents/c_projects/wxWidgets-3.0.5/lib/vc_dll" 
		CACHE PATH "Path to wxWidgets-library *.lib files directory")
		
	SET(WX_WIDGETS_SETUP_PATH 
		"C:/Users/pyotr/Documents/c_projects/wxWidgets-3.0.5/lib/vc_dll/mswu" 
		CACHE PATH "Path to wxWidgets-library includes setup directory (contains setup.h)")
endif(WIN32)

# Compiller flags and options
set(CPP_STANDARD cxx_std_17)


SET(OCCT_LIBS_FILE_LIST
	TKBin.lib
	TKBinL.lib
	TKBinTObj.lib
	TKBinXCAF.lib
	TKBO.lib
	TKBool.lib
	TKBRep.lib
	TKCAF.lib
	TKCDF.lib
	TKD3DHost.lib
	TKD3DHostTest.lib
	TKDCAF.lib
	TKDFBrowser.lib
	TKDraw.lib
	TKernel.lib
	TKFeat.lib
	TKFillet.lib
	TKG2d.lib
	TKG3d.lib
	TKGeomAlgo.lib
	TKGeomBase.lib
	TKHLR.lib
	TKIGES.lib
	TKIVtk.lib
	TKIVtkDraw.lib
	TKLCAF.lib
	TKMath.lib
	TKMesh.lib
	TKMeshVS.lib
	TKMessageModel.lib
	TKMessageView.lib
	TKOffset.lib
	TKOpenGl.lib
	TKOpenGles.lib
	TKOpenGlesTest.lib
	TKOpenGlTest.lib
	TKPrim.lib
	TKQADraw.lib
	TKRWMesh.lib
	TKService.lib
	TKShapeView.lib
	TKShHealing.lib
	TKStd.lib
	TKStdL.lib
	TKSTEP.lib
	TKSTEP209.lib
	TKSTEPAttr.lib
	TKSTEPBase.lib
	TKSTL.lib
	TKTInspector.lib
	TKTInspectorAPI.lib
	TKTObj.lib
	TKTObjDRAW.lib
	TKToolsDraw.lib
	TKTopAlgo.lib
	TKTopTest.lib
	TKTreeModel.lib
	TKV3d.lib
	TKVCAF.lib
	TKView.lib
	TKViewerTest.lib
	TKVInspector.lib
	TKVRML.lib
	TKXCAF.lib
	TKXDEDRAW.lib
	TKXDEIGES.lib
	TKXDESTEP.lib
	TKXMesh.lib
	TKXml.lib
	TKXmlL.lib
	TKXmlTObj.lib
	TKXmlXCAF.lib
	TKXSBase.lib
	TKXSDRAW.lib)
	
SET(WX_WIDGETS_LIBS_FILE_LIST
	wxbase30u.lib
	wxbase30u_net.lib
	wxbase30u_xml.lib
	wxexpat.lib
	wxjpeg.lib
	wxmsw30u_adv.lib
	wxmsw30u_aui.lib
	wxmsw30u_core.lib
	wxmsw30u_gl.lib
	wxmsw30u_html.lib
	wxmsw30u_media.lib
	wxmsw30u_qa.lib
	wxmsw30u_ribbon.lib
	wxmsw30u_richtext.lib
	wxmsw30u_stc.lib
	wxmsw30u_webview.lib
	wxmsw30u_xrc.lib
	wxpng.lib
	wxregexu.lib
	wxscintilla.lib
	wxtiff.lib
	wxzlib.lib)
	
	
add_subdirectory(${SUB_PROJECT_AMADINA_OBJECTS_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_OCCT_NAME})
add_subdirectory(${SUB_PROJECT_wxOCCT_VIEW_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_MAIN})

target_compile_features(${AMADINA_OBJECTS_LIB_NAME} PUBLIC ${CPP_STANDARD})
target_compile_features(${AMADINA_OCCT_LIB_NAME} PUBLIC ${CPP_STANDARD})
target_compile_features(${AMADINA_wxOCCT_LIB_NAME} PUBLIC ${CPP_STANDARD})
target_compile_features(${AMADINA_EXECUTABLE_NAME} PUBLIC ${CPP_STANDARD})



