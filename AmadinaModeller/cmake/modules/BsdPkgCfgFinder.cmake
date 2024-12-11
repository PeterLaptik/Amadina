# Checks whether a library module has been found via pkg_check_modules
# LIB_VAR_PREF - module name prefix
# LIB_NAME - library name, for output messages
function (check_library LIB_VAR_PREF LIB_NAME)
	if(NOT ${LIB_VAR_PREF}_FOUND)
	    message(FATAL_ERROR "Library '${LIB_NAME}' not found.")
	endif()
	message(STATUS "${LIB_VAR_PREF}_CFLAGS=${${LIB_VAR_PREF}_CFLAGS}")
endfunction()