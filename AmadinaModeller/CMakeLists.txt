cmake_minimum_required(VERSION 3.23)

project(AmadinaModeller)

# Output paths for sub-projects: %root_project_dir%/Build (upper level for each sub-project)
set(OUTPUT_DIR_NAME Build)
set(OUTPUT_PATH ../${OUTPUT_DIR_NAME}) 
set(OUTPUT_RUNTIME_PATH ${OUTPUT_PATH}/bin)
set(OUTPUT_ARCH_PATH ${OUTPUT_PATH}/lib)
set(OUTPUT_LIB_PATH ${OUTPUT_PATH}/lib)

# Modules-helpers path: ./cmake/
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(FsUtils)
include(FsUtilsWinPaths)

# Project settings files
set(PROJECT_VARIABLES_FILENAME CMake.vars.txt)
set(PROJECT_VARIABLES_LISTS_FILENAME CMake.vars.lists.txt)

# File containing list of dependency path variables.
# Only for Windows OS
set(WINDOWS_DEPENDENCIES_FILENAME CMake.win.paths.txt) # in the form of KEY=VALUE
set(WINDOWS_DEPENDENCIES_TP_DLLS CMake.win.dlls.txt)      # list of paths, see comment inside

# Setting up dependencies.
if(WIN32)
    # Full list of required dependencies see in CMake.win.paths.txt (WINDOWS_DEPENDENCIES_FILENAME)
    read_dependencies_from_file(${WINDOWS_DEPENDENCIES_FILENAME})

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

# Read additional information from setting files
read_variables_from_file(${PROJECT_VARIABLES_FILENAME})
read_list_variables_from_file(${PROJECT_VARIABLES_LISTS_FILENAME})

set(A_VERSION ${A_VERSION_MAJOR}.${A_VERSION_MINOR}.${A_VERSION_PATH})
message(STATUS "Project version: ${A_VERSION}")

# Sub-projects names
set(SUB_PROJECT_AMADINA_OBJECTS_NAME AmadinaObjects)
set(SUB_PROJECT_AMADINA_OCCT_NAME AmadinaOCCT)
set(SUB_PROJECT_AMADINA_WX_OCCT_NAME AmadinaWxOcct)
set(SUB_PROJECT_AMADINA_COMMAND AmadinaCommand)
set(SUB_PROJECT_AMADINA_MAIN AmadinaModeller)

# Output file names
set(AMADINA_OBJECTS_OUT_NAME amadina_objects_${A_VERSION})
set(AMADINA_OCCT_OUT_NAME amadina_occt_${A_VERSION})
set(AMADINA_WX_OCCT_OUT_NAME amadina_wx_occt_${A_VERSION})
set(AMADINA_COMMAND_OUT_NAME amadina_command_${A_VERSION})
set(AMADINA_EXECUTABLE_OUT_NAME Amadina3D_${A_VERSION})

# Sub projects
add_subdirectory(${SUB_PROJECT_AMADINA_COMMAND})
add_subdirectory(${SUB_PROJECT_AMADINA_OBJECTS_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_OCCT_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_WX_OCCT_NAME})
add_subdirectory(${SUB_PROJECT_AMADINA_MAIN})


add_custom_target(win_fetch_dlls
    "Powershell" "./package_creator.cmd" 
        "${OUTPUT_DIR_NAME}"
        "${WINDOWS_DEPENDENCIES_TP_DLLS}"
        "${WX_WIDGETS_EXECUTABLE}"
        "${OPENCASCADE_EXECUTABLE}"
) 
