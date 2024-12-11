cmake_minimum_required(VERSION 3.25)

# TODO: settings info

project(AmadinaModeller)

# Project output paths: %root_project_dir%/Build
# (setting up for sub-projects)
set(OUTPUT_DIR_NAME Build)
set(OUTPUT_PATH ../${OUTPUT_DIR_NAME}) 
set(OUTPUT_RUNTIME_PATH ${OUTPUT_PATH}/bin)
set(OUTPUT_LIB_PATH ${OUTPUT_PATH}/lib)
set(OUTPUT_ARCH_PATH ${OUTPUT_PATH}/lib)

# Modules-helpers path: ./cmake/
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
include(FsUtils)			# reading variables from text files
include(FsUtilsWinPaths) 	# checking directories existence / searching lib-files
include(BsdPkgCfgFinder)	# checking pkg_check_modules results

# Project settings files
set(CMAKE_TXT_SETTINGS_PATH ./cmake)
set(PROJECT_VERSION_FILENAME version.txt)
set(PROJECT_VARIABLES_LISTS_FILENAME ${CMAKE_TXT_SETTINGS_PATH}/CMake.vars.lists.txt)
set(WINDOWS_DEPENDENCIES_FILENAME ${CMAKE_TXT_SETTINGS_PATH}/CMake.win.paths.txt)
set(WINDOWS_DEPENDENCIES_TP_DLLS_FILENAME ${CMAKE_TXT_SETTINGS_PATH}/CMake.win.dlls.txt)

# Read settings
read_variables_from_file(${PROJECT_VERSION_FILENAME})
read_list_variables_from_file(${PROJECT_VARIABLES_LISTS_FILENAME})

set(A_VERSION ${A_VERSION_MAJOR}.${A_VERSION_MINOR}.${A_VERSION_PATCH})
message(STATUS "Project version: ${A_VERSION}")

# Setting up dependencies.
if(WIN32) # Windows 
    # Full list of required dependencies see in CMake.win.paths.txt 
    read_variables_from_file(${WINDOWS_DEPENDENCIES_FILENAME})

    check_win_path(${BOOST_ROOT_DIR} "Boost library")
    check_win_path(${OPENCASCADE_EXECUTABLE} "OpenCASCADE executable (.dll)")
    check_win_path(${OPENCASCADE_ROOT_DIR} "OpenCASCADE root")
    check_win_path(${OPENCASCADE_INCLUDE_DIRS} "OpenCASCADE include dir")
    check_win_path(${OPENCASCADE_LIBRARIES} "OpenCASCADE libraries (.lib)")
    check_win_path(${WX_WIDGETS_ROOT_DIR} "wxWidgets root")
    check_win_path(${WX_WIDGETS_INCLUDE_DIRS} "wxWidgets include dir")
    check_win_path(${WX_WIDGETS_INCLUDE_SETUP_H_DIR} "wxWidgets include setup dir")
    check_win_path(${WX_WIDGETS_LIBRARIES} "wxWidgets libraries (.lib)")
    check_win_path(${WX_WIDGETS_EXECUTABLE} "wxWidgets executable (.dll)")

    set(OPENCASCADE_LIBS_FILES)
    find_lib_files(OPENCASCADE_LIBS_FILES ${OPENCASCADE_LIBRARIES})
    message(STATUS "OpenCASCADE lib files: ${OPENCASCADE_LIBS_FILES}")
    
    set(WX_WIDGETS_LIBS_FILES)
    find_lib_files(WX_WIDGETS_LIBS_FILES ${WX_WIDGETS_LIBRARIES})
    message(STATUS "wxWidgets lib files: ${WX_WIDGETS_LIBRARIES}")
endif()

if(BSD) # FreeBSD
    message(STATUS "BOOST_ROOT_DIR=${BOOST_ROOT_DIR}")
    message(STATUS "OPENCASCADE_ROOT_DIR=${OPENCASCADE_ROOT_DIR}")
    message(STATUS "OPENCASCADE_INCLUDE_DIRS=${OPENCASCADE_INCLUDE_DIRS}")
    message(STATUS "OPENCASCADE_LIBRARIES=${OPENCASCADE_LIBRARIES}")
    
    message(STATUS "OpenCASCADE shared objectsXX: ${OPENCASCADE_LIBS_FILES}")
    
    string(REPLACE " " ";" OPENCASCADE_LIBS_FILES ${OPENCASCADE_LIBS_FILES})
    message(STATUS "OpenCASCADE shared objects: ${OPENCASCADE_LIBS_FILES}")
    
    string(REPLACE " " ";" WX_WIDGETS_CXX_FLAGS ${WX_WIDGETS_CXX_FLAGS})
    message(STATUS "WX_WIDGETS_CXX_FLAGS = ${WX_WIDGETS_CXX_FLAGS}")
    
    string(REPLACE " " ";" WX_WIDGETS_LIBS_FLAGS ${WX_WIDGETS_LIBS_FLAGS})
    message(STATUS "WX_WIDGETS_LIBS_FLAGS = ${WX_WIDGETS_LIBS_FLAGS}")
    
    find_package(PkgConfig)
    if (NOT PKG_CONFIG_FOUND)
        message(FATAL_ERROR "Module pkg-config has not been found.")
    endif()
    
    pkg_check_modules(GTK "gtk+-3.0")
    check_library(GTK "gtk+-3.0")
    
    pkg_check_modules(GLIB "glib-2.0")
    check_library(GLIB "glib-2.0")
    
    pkg_check_modules(PANGO "pango")
    check_library(PANGO "pango")
    
    pkg_check_modules(GDK_PIX_BUF "gdk-pixbuf-2.0")
    check_library(GDK_PIX_BUF "gdk-pixbuf-2.0")
    
    pkg_check_modules(ATK "atk")
    check_library(ATK "atk")
endif()

# Sub-projects names
set(SUB_PROJECT_AMADINA_OBJECTS_NAME AmadinaObjects)
set(SUB_PROJECT_AMADINA_OCCT_NAME AmadinaOCCT)
set(SUB_PROJECT_AMADINA_WX_OCCT_PANEL_NAME AmadinaWxOcctPanel)
set(SUB_PROJECT_AMADINA_WX_OCCT_NAME AmadinaWxOcct)
set(SUB_PROJECT_AMADINA_WIDGETS_NAME AmadinaWidgets)
set(SUB_PROJECT_AMADINA_COMMAND_NAME AmadinaCommand)
set(SUB_PROJECT_AMADINA_MAIN AmadinaModeller)

# Output file names
set(AMADINA_OBJECTS_OUT_NAME amadina_objects_${A_VERSION})
set(AMADINA_OCCT_OUT_NAME amadina_occobjects_${A_VERSION})
set(AMADINA_WX_OCCT_PANEL_OUT_NAME amadina_wxcanvas_${A_VERSION})
set(AMADINA_WX_OCCT_OUT_NAME amadina_wxocc_${A_VERSION})
set(AMADINA_WIDGETS_OUT_NAME amadina_widgets_${A_VERSION})
set(AMADINA_COMMAND_OUT_NAME amadina_cmd_${A_VERSION})
set(AMADINA_EXECUTABLE_OUT_NAME Amadina3D_${A_VERSION})

# Sub projects
add_subdirectory(${SUB_PROJECT_AMADINA_OBJECTS_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_OCCT_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_WX_OCCT_PANEL_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_WX_OCCT_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_WIDGETS_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_COMMAND_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_MAIN})

add_custom_target(win_fetch_dlls
    "Powershell" "./scripts/win_copy_deps_dlls.cmd" 
        "${OUTPUT_DIR_NAME}"
        "${WINDOWS_DEPENDENCIES_TP_DLLS_FILENAME}"
        "${WX_WIDGETS_EXECUTABLE}"
        "${OPENCASCADE_EXECUTABLE}"
) 
