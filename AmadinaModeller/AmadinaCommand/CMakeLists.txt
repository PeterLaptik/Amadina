cmake_minimum_required(VERSION 3.23)

project(${SUB_PROJECT_AMADINA_COMMAND})

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT (CMAKE_GENERATOR MATCHES "Visual Studio") )
   set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(SRC_PATH src)
set(INCLUDE_PATH include)

set(SOURCE_FILE_LIST
    ${INCLUDE_PATH}/command_functions_def.h    
	${INCLUDE_PATH}/command_parser.h  
	${INCLUDE_PATH}/command_token.h
    ${INCLUDE_PATH}/parser_exception.h
	${INCLUDE_PATH}/grammars/variables/var_ast.h  
	${INCLUDE_PATH}/grammars/variables/var_grammar.h
    ${INCLUDE_PATH}/grammars/variables/var_assigner.h
    ${INCLUDE_PATH}/grammars/calculator/base_calculator.h
	${INCLUDE_PATH}/grammars/calculator/calc_ast.h 
    ${INCLUDE_PATH}/grammars/calculator/calc_evaluator.h     
	${INCLUDE_PATH}/grammars/calculator/calc_executor.h
    ${INCLUDE_PATH}/grammars/calculator/calc_functions.h    
	${INCLUDE_PATH}/grammars/calculator/calc_grammar.h  
	${INCLUDE_PATH}/grammars/calculator/calc_operations.h
	${SRC_PATH}/command_parser.cpp  
	${SRC_PATH}/command_token.cpp
	${SRC_PATH}/grammars/calculator/base_calculator.cpp  
	${SRC_PATH}/grammars/calculator/calc_evaluator.cpp  
	${SRC_PATH}/grammars/calculator/calc_executor.cpp  
	${SRC_PATH}/grammars/calculator/calc_functions.cpp
    ${SRC_PATH}/grammars/command_line/command_transformer.cpp
    ${SRC_PATH}/grammars/variables/var_assigner.cpp
)

add_library(${AMADINA_COMMAND_OUT_NAME} SHARED ${SOURCE_FILE_LIST})

set_target_properties(${AMADINA_COMMAND_OUT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ARCH_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_RUNTIME_PATH}
)
		
target_include_directories(${AMADINA_COMMAND_OUT_NAME} PRIVATE ${INCLUDE_PATH})
target_include_directories(${AMADINA_COMMAND_OUT_NAME} PRIVATE ${BOOST_ROOT_DIR})
