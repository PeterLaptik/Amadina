cmake_minimum_required(VERSION 3.23)

project(AmadinaModeller)

# Dependencies
# Following dependencies paths variables are used (example: see CMake.win.paths.txt):
# - BOOST_PATH - boost library root directory                   
# - OPENCASCADE_PATH - OpenCASCADE library root directory  
# - OPENCASCADE_INCLUDE_PATH - OPENCASCADE_PATH/inc
# - OPENCASCADE_LIB_PATH - Path to OpenCASCADE *.lib files directory
# - WX_WIDGETS_PATH - wxWidgets library root directory 
# - WX_WIDGETS_INCLUDE_PATH = WX_WIDGETS_PATH/include 
# - WX_WIDGETS_LIBS_PATH - Path to wxWidgets-library *.lib files directory
# - WX_WIDGETS_SETUP_PATH - Path to wxWidgets-library includes setup directory, contains setup.h


# File containing list of dependency path variables (in the form of KEY=VALUE). 
# Only for Windows OS: all dependencies paths should be written into the file
set(WINDOWS_DEPENDENCIES_FILENAME CMake.win.paths.txt)

# Setting up dependency environment.
if(WIN32)
    # Read and assign dependency path variables from external file
    file(STRINGS ./${WINDOWS_DEPENDENCIES_FILENAME} WIN_PATHS)
    message(STATUS "Setting up path values from the file: '${WINDOWS_DEPENDENCIES_FILENAME}'")
    foreach(LINE ${WIN_PATHS})
        string(REGEX MATCH "(.*)=(.*)" _ ${LINE})
        set(${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
        message(STATUS "\t ${CMAKE_MATCH_1} = ${CMAKE_MATCH_2}")
    endforeach()

    # Check directory existence for the paths
    function (check_win_path ARG_PATH ARG_LIB_TXT_NAME)
        if(EXISTS ${ARG_PATH})
            message(STATUS "Checking ${ARG_LIB_TXT_NAME} path: (${ARG_PATH})\t OK")
        else()
            message(FATAL_ERROR "\nThe ${ARG_LIB_TXT_NAME} has not been found on the machine. Expecting path: ${ARG_PATH} Input correct path into the file ${WINDOWS_DEPENDENCIES_FILENAME}!")
        endif()
    endfunction()

    check_win_path(${BOOST_PATH} "Boost library")
    check_win_path(${OPENCASCADE_PATH} "OpenCASCADE library")
    check_win_path(${OPENCASCADE_LIB_PATH} "OpenCASCADE library lib dir")
    check_win_path(${WX_WIDGETS_PATH} "wxWidgets library")
    check_win_path(${WX_WIDGETS_LIBS_PATH} "wxWidgets library lib dir")
    check_win_path(${WX_WIDGETS_SETUP_PATH} "wxWidgets library setup dir")
    
    set(WX_WIDGETS_INCLUDE_PATH ${WX_WIDGETS_PATH}/include)
    set(OPENCASCADE_INCLUDE_PATH ${OPENCASCADE_PATH}/inc)
    check_win_path(${WX_WIDGETS_INCLUDE_PATH} "wxWidgets include path")
    check_win_path(${OPENCASCADE_INCLUDE_PATH} "OpenCASCADE include path")
    
    # Find dependencies lib-files
    function (find_lib_files OUT_NAME ARG_PATH)
        message(STATUS "Searching libs: ${ARG_PATH}")
        set(FN_RESULT)
        file(GLOB LIB_FILES_LIST ${ARG_PATH}/*.lib)
        
        list(LENGTH LIB_FILES_LIST RES_LEN)
        if(RES_LEN EQUAL 0)
            message(FATAL_ERROR "Could not find lib files in ${ARG_PATH}")
        endif()
        
        foreach(LINE ${LIB_FILES_LIST})
            string(REGEX MATCH "([^\/]+$)" _ ${LINE})
            string(CONCAT FN_RESULT ${FN_RESULT} " " ${CMAKE_MATCH_1})
        endforeach()
        set(${OUT_NAME} ${FN_RESULT} PARENT_SCOPE)
    endfunction()
    
    set(OPENCASCADE_LIBS_FILES)
    find_lib_files(OPENCASCADE_LIBS_FILES ${OPENCASCADE_LIB_PATH})
    message(STATUS "OpenCASCADE lib files: ${OPENCASCADE_LIBS_FILES}")
    
    set(WX_WIDGETS_LIBS_FILES)
    find_lib_files(WX_WIDGETS_LIBS_FILES ${WX_WIDGETS_LIBS_PATH})
    message(STATUS "wxWidgets lib files: ${WX_WIDGETS_LIBS_FILES}")

endif()

# Sub-projects names
#set(SUB_PROJECT_AMADINA_OBJECTS_NAME AmadinaObjects)
#set(SUB_PROJECT_AMADINA_OCCT_NAME AmadinaOCCT)
#set(SUB_PROJECT_wxOCCT_VIEW_NAME wxOcctView)
set(SUB_PROJECT_AMADINA_COMMAND AmadinaCommand)
#set(SUB_PROJECT_AMADINA_MAIN AmadinaModeller)

# Output file names
#set(AMADINA_OBJECTS_LIB_NAME amadina_objects)
#set(AMADINA_OCCT_LIB_NAME amadina_occt)
#set(AMADINA_wxOCCT_LIB_NAME amadina_wxocct)
set(SUB_PROJECT_AMADINA_OUT_NAME amadina_command)
#set(AMADINA_EXECUTABLE_NAME Amadina3D)

add_subdirectory(${SUB_PROJECT_AMADINA_COMMAND})
    
