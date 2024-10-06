# Checks whether a module has been found
# LIB_VAR_PREF - module name prefix
# LIB_NAME - library name
function (find_library_check LIB_VAR_PREF LIB_NAME)
	if(NOT ${LIB_VAR_PREF}_FOUND)
	    message(FATAL_ERROR "Library '${LIB_NAME}' not found.")
	endif()
	message(STATUS "${LIB_VAR_PREF}_CFLAGS=${${LIB_VAR_PREF}_CFLAGS}")
endfunction()