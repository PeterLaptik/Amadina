cmake_minimum_required(VERSION 3.23)

project(${SUB_PROJECT_AMADINA_COMMAND_NAME})

set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT (CMAKE_GENERATOR MATCHES "Visual Studio") )
   set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

set(SRC_PATH src)
set(INCLUDE_PATH include)
set(INCLUDE_SRC ${SRC_PATH})
set(AMADINA_OBJECTS_INCLUDE_PATH ../${SUB_PROJECT_AMADINA_OBJECTS_NAME}/include)

link_directories(${OPENCASCADE_LIBRARIES})
link_directories(${OUTPUT_LIB_PATH})

set(SOURCE_FILE_LIST
	${INCLUDE_PATH}/base_command.h  
	${INCLUDE_PATH}/application_context.h  
	${INCLUDE_PATH}/sheet_context.h  
	${INCLUDE_PATH}/command_parser.h  
	${INCLUDE_PATH}/command_token.h
    ${INCLUDE_PATH}/parser_exception.h
	${SRC_PATH}/command_dispatcher.h 
    ${SRC_PATH}/command_functions_def.h   
	${SRC_PATH}/grammars/variables/var_ast.h  
	${SRC_PATH}/grammars/variables/var_grammar.h
    ${SRC_PATH}/grammars/variables/var_assigner.h
    ${SRC_PATH}/grammars/calculator/base_calculator.h
	${SRC_PATH}/grammars/calculator/calc_ast.h 
    ${SRC_PATH}/grammars/calculator/calc_evaluator.h     
	${SRC_PATH}/grammars/calculator/calc_executor.h
    ${SRC_PATH}/grammars/calculator/calc_functions.h    
	${SRC_PATH}/grammars/calculator/calc_grammar.h  
	${SRC_PATH}/grammars/calculator/calc_operations.h
	${SRC_PATH}/commands/create_sketch.h
	${SRC_PATH}/application_context.cpp  
	${SRC_PATH}/sheet_context.cpp  
	${SRC_PATH}/command_dispatcher.cpp
	${SRC_PATH}/command_parser.cpp  
	${SRC_PATH}/command_token.cpp
	${SRC_PATH}/grammars/calculator/base_calculator.cpp  
	${SRC_PATH}/grammars/calculator/calc_evaluator.cpp  
	${SRC_PATH}/grammars/calculator/calc_executor.cpp  
	${SRC_PATH}/grammars/calculator/calc_functions.cpp
    ${SRC_PATH}/grammars/command_line/command_transformer.cpp
    ${SRC_PATH}/grammars/variables/var_assigner.cpp
	${SRC_PATH}/commands/create_sketch.cpp
)

add_library(${AMADINA_COMMAND_OUT_NAME} SHARED ${SOURCE_FILE_LIST})

set_target_properties(${AMADINA_COMMAND_OUT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ARCH_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIB_PATH}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_RUNTIME_PATH}
)

target_link_libraries(${AMADINA_COMMAND_OUT_NAME} PRIVATE ${AMADINA_OBJECTS_OUT_NAME})

target_include_directories(${AMADINA_COMMAND_OUT_NAME} PRIVATE ${INCLUDE_PATH})
target_include_directories(${AMADINA_COMMAND_OUT_NAME} PRIVATE ${INCLUDE_SRC})

target_include_directories(${AMADINA_COMMAND_OUT_NAME} PRIVATE ${AMADINA_OBJECTS_INCLUDE_PATH})
target_include_directories(${AMADINA_COMMAND_OUT_NAME} PRIVATE ${BOOST_ROOT_DIR})
