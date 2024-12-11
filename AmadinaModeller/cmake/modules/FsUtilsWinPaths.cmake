# A set of helper functions for Windows paths and files searching / checking

# Checks a directory existence for the path
# ARG_PATH - path to a library
# ARG_LIB_TXT_NAME - library name, for output messages
function (check_win_path ARG_PATH ARG_LIB_TXT_NAME)
    if(EXISTS ${ARG_PATH})
        message(STATUS "Checking ${ARG_LIB_TXT_NAME} path: (${ARG_PATH})\t OK")
    else()
        message(FATAL_ERROR "\nThe ${ARG_LIB_TXT_NAME} has not been found on the machine. Expecting path: ${ARG_PATH} Input correct path into the file ${WINDOWS_DEPENDENCIES_FILENAME}!")
    endif()
endfunction()


# Finds lib-files in a directory
# OUT_NAME - name of a variable to put a .lib-files list
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