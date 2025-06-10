cmake_minimum_required(VERSION 3.25)

project(AmadinaModeller)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Project: ${CMAKE_PROJECT_NAME}")
message(STATUS "Arch: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Project output paths: %root_project_dir%/Build/TYPE_ARCH
set(OUTPUT_DIR_NAME Build/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_PROCESSOR})
set(OUTPUT_DIR_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT_DIR_NAME}) 
set(OUTPUT_RUNTIME_PATH ${OUTPUT_DIR_PATH}/bin)
set(OUTPUT_LIB_PATH ${OUTPUT_DIR_PATH}/lib)
set(OUTPUT_ARCH_PATH ${OUTPUT_DIR_PATH}/lib)
set(OUTPUT_SHARE_PATH ${OUTPUT_DIR_PATH}/share)
message(STATUS "Project build dir: ./${OUTPUT_DIR_NAME}")

# Additional local modules-helpers
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
include(FsUtils)    # reading variables from text files

# Project settings files
set(PROJECT_VERSION_FILENAME version.txt)

# Read settings files
read_variables_from_file(${PROJECT_VERSION_FILENAME})
set(A_VERSION ${A_VERSION_MAJOR}.${A_VERSION_MINOR}.${A_VERSION_PATCH})
message(STATUS "Project version: ${A_VERSION}")

# Setting up dependencies.
find_package(OpenCASCADE COMPONENTS FoundationClasses REQUIRED)
message (STATUS "OpenCASCADE found = ${OpenCASCADE_FOUND}")
message (STATUS "OpenCASCADE_VERSION = ${OpenCASCADE_VERSION}")
message (STATUS "OpenCASCADE_INCLUDE_DIR = ${OpenCASCADE_INCLUDE_DIR}")
message (STATUS "OpenCASCADE_LIBRARY_DIR = ${OPENCASCADE_LIBRARY_DIR}")
message (STATUS "OpenCASCADE_BINARY_DIR = ${OpenCASCADE_BINARY_DIR}")
message (STATUS "OpenCASCADE_LIBRARIES = ${OpenCASCADE_LIBRARIES}")

find_package(Boost CONFIG REQUIRED)
message (STATUS "Boost found = ${Boost_FOUND}")
message (STATUS "Boost_VERSION_STRING = ${Boost_VERSION_STRING}")
message (STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")

find_package(wxWidgets COMPONENTS core base OPTIONAL_COMPONENTS aui ribbon REQUIRED)
message (STATUS "wxWidgets found = ${wxWidgets_FOUND}")
message (STATUS "wxWidgets_VERSION_STRING = ${wxWidgets_VERSION_STRING}")
message (STATUS "wxWidgets_LIBRARIES = ${wxWidgets_LIBRARIES}")
message (STATUS "wxWidgets_INCLUDE_DIRS = ${wxWidgets_INCLUDE_DIRS}")
message (STATUS "wxWidgets_LIBRARY_DIR = ${wxWidgets_LIBRARY_DIR}")
message (STATUS "wxWidgets_BINARY_DIR = ${wxWidgets_BINARY_DIR}")
message (STATUS "wxWidgets_DEFINITIONS  = ${wxWidgets_DEFINITIONS}")
message (STATUS "wxWidgets_DEFINITIONS_DEBUG  = ${wxWidgets_DEFINITIONS_DEBUG}")
message (STATUS "wxWidgets_CXX_FLAGS  = ${wxWidgets_CXX_FLAGS}")
message (STATUS "wxWidgets_LIBRARIES = ${wxWidgets_LIBRARIES}")

# TODO Remove?
if(WIN32)
	find_package(vtk REQUIRED)
	message (STATUS "vtk found = ${vtk_FOUND}")
	message (STATUS "VTK_LIBRARY_DIRS = ${vtk_LIBRARY_DIRS}")
	message (STATUS "vtk_LIBRARY_DIR = ${vtk_LIBRARY_DIR}")
	message (STATUS "vtk_INCLUDE_DIRS = ${vtk_INCLUDE_DIRS}")
	message (STATUS "VTK_BUILD_VERSION = ${vtk_BUILD_VERSION}")
endif()

if(BSD)
	find_package(X11 REQUIRED)
	message (STATUS "X11 found = ${X11_FOUND}")
	message (STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
	
	find_package(PkgConfig REQUIRED)
	
	pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
	message (STATUS "GTK3_INCLUDE_DIRS = ${GTK3_INCLUDE_DIRS}")
endif()


# Project contents
# Sub-projects names
set(SUB_PROJECT_AMADINA_OBJECTS_NAME AmadinaObjects)
set(SUB_PROJECT_AMADINA_OCCT_NAME AmadinaOCCT)
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
set(AMADINA_EXECUTABLE_OUT_NAME amadina-3D-${A_VERSION})

# Sub projects
add_subdirectory(${SUB_PROJECT_AMADINA_OBJECTS_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_OCCT_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_WX_OCCT_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_WIDGETS_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_COMMAND_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_MAIN})


# Additional custom targets
add_custom_target(win_fetch_dlls
    "Powershell" "./scripts/win_copy_deps_dlls.cmd" 
        "${OUTPUT_DIR_NAME}"
        "${WINDOWS_DEPENDENCIES_TP_DLLS_FILENAME}"
        "${WX_WIDGETS_EXECUTABLE}"
        "${OPENCASCADE_EXECUTABLE}"
) 

add_custom_target(copy_share_files)
add_custom_command(
        TARGET copy_share_files POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/share
                ${OUTPUT_SHARE_PATH})
add_dependencies(${AMADINA_EXECUTABLE_OUT_NAME} copy_share_files)