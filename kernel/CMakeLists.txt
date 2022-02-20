cmake_minimum_required(VERSION 3.0)

# Paths to kernel translation units
set(DIR_KERNEL_ENTITIES 	"entities/")
set(DIR_KERNEL_GEOMETRY 	"geometry/")
set(DIR_KERNEL_GRAPHICS 	"graphics/")
set(DIR_KERNEL_PROCESSOR 	"processor/")
set(DIR_KERNEL_VIEWS 		"view_2d/")
set(DIR_KERNEL_CONTEXT 		"context/")
set(DIR_KERNEL_COMMAND 		"command/")
set(DIR_KERNEL_BUILDERS 	"builders/")

add_library(amadina_kernel SHARED "")

set_target_properties(amadina_kernel PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED ON)

target_sources(amadina_kernel 
		PRIVATE 
			${DIR_KERNEL_ENTITIES}layer.cpp
			${DIR_KERNEL_ENTITIES}arc.cpp
			${DIR_KERNEL_ENTITIES}circle.cpp
			${DIR_KERNEL_ENTITIES}line.cpp
			${DIR_KERNEL_ENTITIES}point.cpp
			${DIR_KERNEL_ENTITIES}entity.cpp
)

target_sources(amadina_kernel 
		PRIVATE 
			${DIR_KERNEL_GEOMETRY}geometry.cpp
			${DIR_KERNEL_GEOMETRY}intersections.cpp
)

target_sources(amadina_kernel 
		PRIVATE 
			${DIR_KERNEL_GRAPHICS}colour.cpp
)

target_sources(amadina_kernel 
		PRIVATE 
			${DIR_KERNEL_PROCESSOR}drawmanager.cpp
)

target_sources(amadina_kernel 
		PRIVATE 
			${DIR_KERNEL_VIEWS}screen.cpp
)

target_sources(amadina_kernel 
		PRIVATE 
			${DIR_KERNEL_CONTEXT}context.cpp
			${DIR_KERNEL_CONTEXT}command_pool.cpp
			${DIR_KERNEL_CONTEXT}command_executor.cpp
			${DIR_KERNEL_CONTEXT}clipboard.cpp
)

target_sources(amadina_kernel 
		PRIVATE 
			${DIR_KERNEL_COMMAND}command.cpp
			${DIR_KERNEL_COMMAND}acommand.cpp
			${DIR_KERNEL_COMMAND}dispatcher.cpp
			${DIR_KERNEL_COMMAND}interpreter.cpp
			${DIR_KERNEL_COMMAND}lexer.cpp
)

target_sources(amadina_kernel 
		PRIVATE 
			${DIR_KERNEL_BUILDERS}point_cmd.cpp
			${DIR_KERNEL_BUILDERS}line_cmd.cpp
			${DIR_KERNEL_BUILDERS}circle_cmd.cpp
			${DIR_KERNEL_BUILDERS}circlep_cmd.cpp
			${DIR_KERNEL_BUILDERS}arc_cmd.cpp
			${DIR_KERNEL_BUILDERS}arcp_cmd.cpp
			${DIR_KERNEL_BUILDERS}copy_cmd.cpp
			${DIR_KERNEL_BUILDERS}paste_cmd.cpp
			${DIR_KERNEL_BUILDERS}delete_cmd.cpp
)