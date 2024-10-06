# A set of helper functions for Windows paths and files searching and checking

# Read and assign dependency path variables from external file
# FILE_NAME - file name, must be in a root directory
function(read_dependencies_from_file FILE_NAME)
    file(STRINGS ./${FILE_NAME} WIN_PATHS)
    message(STATUS "Setting up paths values from the file: '${WINDOWS_DEPENDENCIES_FILENAME}'")
    foreach(LINE ${WIN_PATHS})
        string(REGEX MATCH "(.*)=(.*)" _ ${LINE})
        set(${CMAKE_MATCH_1} ${CMAKE_MATCH_2} PARENT_SCOPE)
        message(STATUS "\t ${CMAKE_MATCH_1} = ${CMAKE_MATCH_2}")
    endforeach()
endfunction()


# Check directory existence for the paths
# ARG_PATH - path to a library
# ARG_LIB_TXT_NAME - library name, for error messages if a directory is not found
function (check_win_path ARG_PATH ARG_LIB_TXT_NAME)
    if(EXISTS ${ARG_PATH})
        message(STATUS "Checking ${ARG_LIB_TXT_NAME} path: (${ARG_PATH})\t OK")
    else()
        message(FATAL_ERROR "\nThe ${ARG_LIB_TXT_NAME} has not been found on the machine. Expecting path: ${ARG_PATH} Input correct path into the file ${WINDOWS_DEPENDENCIES_FILENAME}!")
    endif()
endfunction()


# Find dependencies lib-files
# OUT_NAME - name of a variable for keeping .lib-files list
# ARG_PATH - a path where to look for .lib-files
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
        list(APPEND FN_RESULT ${CMAKE_MATCH_1})
    endforeach()
    set(${OUT_NAME} ${FN_RESULT} PARENT_SCOPE)
endfunction()