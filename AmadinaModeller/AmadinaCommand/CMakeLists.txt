cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#TODO REMOVE
set(SUB_PROJECT_AMADINA_COMMAND_NAME AmadinaCommand)
set(BOOST_PATH C:/CPP/boost_1_85_0)
set(EXEC_NAME parser)

project(${SUB_PROJECT_AMADINA_COMMAND_NAME})

set(SRC_PATH src)
set(INCLUDE_PATH include)

add_executable(${EXEC_NAME}
	${INCLUDE_PATH}/command_functions_def.h  
	${INCLUDE_PATH}/command_interpreter.h  
	${INCLUDE_PATH}/command_parser.h  
	${INCLUDE_PATH}/command_token.h
	${INCLUDE_PATH}/variables/var_ast.h  
	${INCLUDE_PATH}/variables/var_grammar.h
	${INCLUDE_PATH}/calculator/calc_ast.h       
	${INCLUDE_PATH}/calculator/calc_executor.h   
	${INCLUDE_PATH}/calculator/calc_grammar.h  
	${INCLUDE_PATH}/calculator/calc_operations.h
	${INCLUDE_PATH}/calculator/calc_evaluator.h  
	${INCLUDE_PATH}/calculator/calc_functions.h  
	${INCLUDE_PATH}/calculator/calc_lexer.h
	${SRC_PATH}/command_interpreter.cpp  
	${SRC_PATH}/command_parser.cpp  
	${SRC_PATH}/command_token.cpp
	${SRC_PATH}/calculator/calc_functions.cpp  
	${SRC_PATH}/calculator/interpreter_evaluator.cpp  
	${SRC_PATH}/calculator/interpreter_executor.cpp  
	${SRC_PATH}/calculator/interpreter_lexer.cpp
	test/main.cpp
)
		
target_include_directories(${EXEC_NAME} PRIVATE ${INCLUDE_PATH})
target_include_directories(${EXEC_NAME} PRIVATE ${BOOST_PATH})