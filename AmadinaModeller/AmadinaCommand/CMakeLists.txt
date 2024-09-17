cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(OUTPUT_PATH ../Build)

#TODO REMOVE
#set(SUB_PROJECT_AMADINA_COMMAND_NAME AmadinaCommand)
#set(BOOST_PATH C:/CPP/boost_1_85_0)
#set(EXEC_NAME amadina_command)
#set(TEST_NAME test_command)

project(${SUB_PROJECT_AMADINA_COMMAND})

set(SRC_PATH src)
set(INCLUDE_PATH include)
set(TEST_PATH test)

set(SOURCE_FILE_LIST
    ${INCLUDE_PATH}/command_functions_def.h  
	${INCLUDE_PATH}/command_interpreter.h  
	${INCLUDE_PATH}/command_parser.h  
	${INCLUDE_PATH}/command_token.h
    ${INCLUDE_PATH}/parser_exception.h
	${INCLUDE_PATH}/variables/var_ast.h  
	${INCLUDE_PATH}/variables/var_grammar.h
    ${INCLUDE_PATH}/variables/var_assigner.h
    ${INCLUDE_PATH}/calculator/base_calculator.h
	${INCLUDE_PATH}/calculator/calc_ast.h 
    ${INCLUDE_PATH}/calculator/calc_evaluator.h     
	${INCLUDE_PATH}/calculator/calc_executor.h
    ${INCLUDE_PATH}/calculator/calc_functions.h    
	${INCLUDE_PATH}/calculator/calc_grammar.h  
	${INCLUDE_PATH}/calculator/calc_operations.h
	${INCLUDE_PATH}/calculator/interpreter_grammar.h
	${SRC_PATH}/command_interpreter.cpp  
	${SRC_PATH}/command_parser.cpp  
	${SRC_PATH}/command_token.cpp
	${SRC_PATH}/calculator/base_calculator.cpp  
	${SRC_PATH}/calculator/calc_evaluator.cpp  
	${SRC_PATH}/calculator/calc_executor.cpp  
	${SRC_PATH}/calculator/calc_functions.cpp
    ${SRC_PATH}/command_line/command_transformer.cpp
    ${SRC_PATH}/variables/var_assigner.cpp
)

add_library(${SUB_PROJECT_AMADINA_OUT_NAME} SHARED ${SOURCE_FILE_LIST})
set_target_properties(${SUB_PROJECT_AMADINA_OUT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_PATH}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_PATH}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_PATH}/bin"
)
		
target_include_directories(${SUB_PROJECT_AMADINA_OUT_NAME} PRIVATE ${INCLUDE_PATH})
target_include_directories(${SUB_PROJECT_AMADINA_OUT_NAME} PRIVATE ${BOOST_PATH})
