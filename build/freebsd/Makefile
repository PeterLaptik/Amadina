
CC = clang++
LN = clang++
DLL_FLAGS = -fPIC
CXX_FLAGS = -Wall -O2
WX_CONFIG_CPP = `wx-config --cppflags`
WX_CONFIG_LINKER = `wx-config --libs all`

# Output files
OUT_GUI = amadina
OUT_KERNEL = libamadina_kernel.so
OUT_WX = libamadina_wx.so

# Output directory paths
MKDIR_P = mkdir -p
DIR_BIN = bin
DIR_OBJ = obj
DIR_KERNEL = kernel
DIR_KERNEL_OBJ = ${DIR_OBJ}/${DIR_KERNEL}

# Source paths
SRC_KERNEL = ../../kernel
SRC_ENTITIES = ${SRC_KERNEL}/entities
SRC_SCREEN = ${SRC_KERNEL}/view_2d
SRC_GRAPHICS = ${SRC_KERNEL}/graphics
SRC_GEOMETRY= ${SRC_KERNEL}/geometry
SRC_PROCESSOR= ${SRC_KERNEL}/processor
SRC_CONTEXT= ${SRC_KERNEL}/context
SRC_COMMAND= ${SRC_KERNEL}/command
SRC_BUILDERS= ${SRC_KERNEL}/builders
SRC_WXBINDING = ../../wx_binding
SRC_AMADINA = ../../amadina

#Dependencies

.PHONY: directories

all: directories kernel wx_binding gui

KERNEL_ENTITIES_OBJ = entity.o point.o line.o arc.o circle.o
KERNEL_COMMAND_OBJ = acommand.o command.o dispatcher.o interpreter.o lexer.o
KERNEL_CONTEXT_OBJ = clipboard.o command_executor.o command_pool.o context.o
KERNEL_SCREEN_OBJ = screen.o
KERNEL_PROCESSOR_OBJ = drawmanager.o
KERNEL_GEOMETRY_OBJ = geometry.o intersections.o
KERNEL_GRAPHICS_OBJ = colour.o
KERNEL_BUILDERS_OBJ = point_cmd.o line_cmd.o circle_cmd.o arc_cmd.o arcp_cmd.o \
				copy_cmd.o delete_cmd.o paste_cmd.o
WX_BINDING_OBJ = events.o viewpanel.o dcadapter_wx.o wx_binding.o wx_objects.o provider.o
GUI_OBJ = amadin_app.o main_frame.o wxchoicelayer.o toolbar_items.o uiconsole.o menu.o layer.o

# Amadina GUI
gui: gui_classes
	${LN} ${GUI_OBJ} ${OUT_KERNEL} ${OUT_WX} ${WX_CONFIG_LINKER} -o ${OUT_GUI}


gui_classes: ${GUI_OBJ}

amadin_app.o: ${SRC_AMADINA}/amadin_app.h ${SRC_AMADINA}/amadin_app.cpp
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} -I${SRC_WXBINDING} ${WX_CONFIG_CPP} \
	${SRC_AMADINA}/amadin_app.cpp  ${DLL_FLAGS}
main_frame.o: ${SRC_AMADINA}/menu/*.h ${SRC_AMADINA}/events/*.h \
	${SRC_AMADINA}/main_frame.h ${SRC_AMADINA}/main_frame.cpp
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} -I${SRC_WXBINDING} ${WX_CONFIG_CPP} \
	${SRC_AMADINA}/main_frame.cpp  ${DLL_FLAGS}
wxchoicelayer.o: ${SRC_AMADINA}/menu/*.h ${SRC_AMADINA}/events/*.h \
	${SRC_AMADINA}/wxchoicelayer.cpp ${SRC_AMADINA}/wxchoicelayer.h
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} -I${SRC_WXBINDING} ${WX_CONFIG_CPP} \
	${SRC_AMADINA}/wxchoicelayer.cpp  ${DLL_FLAGS}
toolbar_items.o: ${SRC_AMADINA}/widgets/*.h ${SRC_AMADINA}/widgets/*.cpp \
	${SRC_AMADINA}/menu/*.cpp ${SRC_AMADINA}/events/*.h
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} -I${SRC_WXBINDING} ${WX_CONFIG_CPP} \
	${SRC_AMADINA}/widgets/toolbar_items.cpp  ${DLL_FLAGS}
uiconsole.o: ${SRC_AMADINA}/menu/*.h ${SRC_AMADINA}/events/*.h \
	${SRC_AMADINA}/widgets/console/*.h ${SRC_AMADINA}/widgets/console/*.cpp
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} -I${SRC_WXBINDING} ${WX_CONFIG_CPP} \
	${SRC_AMADINA}/widgets/console/uiconsole.cpp  ${DLL_FLAGS}
menu.o: ${SRC_AMADINA}/menu/*.h ${SRC_AMADINA}/menu/*.cpp ${SRC_AMADINA}/events/*.h
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} -I${SRC_WXBINDING} ${WX_CONFIG_CPP} \
	${SRC_AMADINA}/menu/menu.cpp  ${DLL_FLAGS}


# Amadina wxWidgets binding library
wx_binding: binding_objects
	${LN} -shared ${WX_BINDING_OBJ} ${OUT_KERNEL} ${WX_CONFIG_LINKER} -o ${OUT_WX}

binding_objects: ${WX_BINDING_OBJ}
events.o: ${SRC_WXBINDING}/classes/*.h ${SRC_WXBINDING}/classes/*.cpp
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} ${WX_CONFIG_CPP} \
	${SRC_WXBINDING}/classes/events.cpp  ${DLL_FLAGS}
viewpanel.o: ${SRC_WXBINDING}/classes/*.h ${SRC_WXBINDING}/classes/*.cpp
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} ${WX_CONFIG_CPP} \
	${SRC_WXBINDING}/classes/viewpanel.cpp  ${DLL_FLAGS}
dcadapter_wx.o: ${SRC_WXBINDING}/classes/*.h ${SRC_WXBINDING}/classes/*.cpp
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} ${WX_CONFIG_CPP} \
	${SRC_WXBINDING}/classes/dcadapter_wx.cpp  ${DLL_FLAGS}
wx_binding.o: ${SRC_WXBINDING}/src/*.h ${SRC_WXBINDING}/src/*.cpp
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} ${WX_CONFIG_CPP} \
	${SRC_WXBINDING}/src/wx_binding.cpp  ${DLL_FLAGS}
wx_objects.o: ${SRC_WXBINDING}/src/*.h ${SRC_WXBINDING}/src/*.cpp
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} ${WX_CONFIG_CPP} \
	${SRC_WXBINDING}/src/wx_objects.cpp  ${DLL_FLAGS}
provider.o: ${SRC_WXBINDING}/res/*.h ${SRC_WXBINDING}/res/*.cpp
	${CC} -c ${CXX_FLAGS} -I${SRC_KERNEL} ${WX_CONFIG_CPP} \
	${SRC_WXBINDING}/res/provider.cpp  ${DLL_FLAGS}
	

# Amadina kernel
kernel: entities geometry graphics processor views context commands builders
	${LN} -shared \
	${KERNEL_ENTITIES_OBJ} \
	${KERNEL_COMMAND_OBJ} \
	${KERNEL_CONTEXT_OBJ} \
	${KERNEL_SCREEN_OBJ} \
	${KERNEL_PROCESSOR_OBJ} \
	${KERNEL_GEOMETRY_OBJ} \
	${KERNEL_GRAPHICS_OBJ} \
	${KERNEL_BUILDERS_OBJ} \
	-o ${OUT_KERNEL}
	@echo **********_Kernel_assembled_********** 

# Entity builders
builders: ${KERNEL_BUILDERS_OBJ} ${SRC_BUILDERS}/*.h ${SRC_BUILDERS}/*.cpp \
	${KERNEL_ENTITIES_OBJ} ${KERNEL_GEOMETRY_OBJ} ${KERNEL_COMMAND_OBJ} \
	${KERNEL_CONTEXT_OBJ}

point_cmd.o:
	${CC} -c ${CXX_FLAGS} ${SRC_BUILDERS}/point_cmd.cpp  ${DLL_FLAGS}
line_cmd.o:
	${CC} -c ${CXX_FLAGS} ${SRC_BUILDERS}/line_cmd.cpp  ${DLL_FLAGS}
circle_cmd.o:
	${CC} -c ${CXX_FLAGS} ${SRC_BUILDERS}/circle_cmd.cpp  ${DLL_FLAGS}
arc_cmd.o:
	${CC} -c ${CXX_FLAGS} ${SRC_BUILDERS}/arc_cmd.cpp  ${DLL_FLAGS}
arcp_cmd.o:
	${CC} -c ${CXX_FLAGS} ${SRC_BUILDERS}/arcp_cmd.cpp  ${DLL_FLAGS}
copy_cmd.o:
	${CC} -c ${CXX_FLAGS} ${SRC_BUILDERS}/copy_cmd.cpp  ${DLL_FLAGS}
delete_cmd.o:
	${CC} -c ${CXX_FLAGS} ${SRC_BUILDERS}/delete_cmd.cpp  ${DLL_FLAGS}
paste_cmd.o:
	${CC} -c ${CXX_FLAGS} ${SRC_BUILDERS}/paste_cmd.cpp  ${DLL_FLAGS}
	

# Commands
commands: ${KERNEL_COMMAND_OBJ}

acommand.o:
	${CC} -c ${CXX_FLAGS} ${SRC_COMMAND}/acommand.cpp  ${DLL_FLAGS}
command.o:
	${CC} -c ${CXX_FLAGS} ${SRC_COMMAND}/command.cpp  ${DLL_FLAGS}
dispatcher.o:
	${CC} -c ${CXX_FLAGS} ${SRC_COMMAND}/dispatcher.cpp  ${DLL_FLAGS}
interpreter.o:
	${CC} -c ${CXX_FLAGS} ${SRC_COMMAND}/interpreter.cpp  ${DLL_FLAGS}
lexer.o:
	${CC} -c ${CXX_FLAGS} ${SRC_COMMAND}/lexer.cpp  ${DLL_FLAGS}


# Context
context: ${KERNEL_CONTEXT_OBJ}

clipboard.o: ${SRC_CONTEXT}/*.h ${SRC_CONTEXT}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_CONTEXT}/clipboard.cpp  ${DLL_FLAGS}
command_executor.o: ${SRC_CONTEXT}/*.h ${SRC_CONTEXT}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_CONTEXT}/command_executor.cpp  ${DLL_FLAGS}
command_pool.o: ${SRC_CONTEXT}/*.h ${SRC_CONTEXT}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_CONTEXT}/command_pool.cpp  ${DLL_FLAGS}
context.o: ${SRC_CONTEXT}/*.h ${SRC_CONTEXT}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_CONTEXT}/context.cpp  ${DLL_FLAGS}


# Views / screens
views: ${KERNEL_SCREEN_OBJ}

screen.o: ${SRC_SCREEN}/*.h ${SRC_SCREEN}/*.cpp drawmanager.o
	${CC} -c ${CXX_FLAGS} ${SRC_SCREEN}/screen.cpp  ${DLL_FLAGS}


# Processor
processor: ${KERNEL_PROCESSOR_OBJ}

drawmanager.o: ${SRC_PROCESSOR}/*.h ${SRC_PROCESSOR}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_PROCESSOR}/drawmanager.cpp  ${DLL_FLAGS}


# Graphics
graphics: ${KERNEL_GRAPHICS_OBJ}

colour.o: ${SRC_GRAPHICS}/*.h ${SRC_GRAPHICS}/*.cpp ${KERNEL_ENTITIES_OBJ}
	${CC} -c ${CXX_FLAGS} ${SRC_GRAPHICS}/colour.cpp  ${DLL_FLAGS}


# Geometry
geometry: ${KERNEL_GEOMETRY_OBJ}

geometry.o: ${SRC_GEOMETRY}/*.h ${SRC_GEOMETRY}/*.cpp ${KERNEL_ENTITIES_OBJ}
	${CC} -c ${CXX_FLAGS} ${SRC_GEOMETRY}/geometry.cpp  ${DLL_FLAGS}
intersections.o: ${SRC_GEOMETRY}/*.h ${SRC_GEOMETRY}/*.cpp ${KERNEL_ENTITIES_OBJ}
	${CC} -c ${CXX_FLAGS} ${SRC_GEOMETRY}/intersections.cpp  ${DLL_FLAGS}


# Kernel entities
entities: ${KERNEL_ENTITIES_OBJ}

layer.o: ${SRC_ENTITIES}/*.h ${SRC_ENTITIES}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_ENTITIES}/layer.cpp  ${DLL_FLAGS}
circle.o: ${SRC_ENTITIES}/*.h ${SRC_ENTITIES}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_ENTITIES}/circle.cpp  ${DLL_FLAGS}
arc.o: ${SRC_ENTITIES}/*.h ${SRC_ENTITIES}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_ENTITIES}/arc.cpp  ${DLL_FLAGS}
line.o: ${SRC_ENTITIES}/*.h ${SRC_ENTITIES}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_ENTITIES}/line.cpp  ${DLL_FLAGS}
point.o: ${SRC_ENTITIES}/*.h ${SRC_ENTITIES}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_ENTITIES}/point.cpp  ${DLL_FLAGS}
entity.o: ${SRC_ENTITIES}/*.h ${SRC_ENTITIES}/*.cpp
	${CC} -c ${CXX_FLAGS} ${SRC_ENTITIES}/entity.cpp  ${DLL_FLAGS}



directories:
	uname -a
	@echo **********_Creating_dirs_**********
#	${MKDIR_P} ${DIR_KERNEL_OBJ}



clean:
	@echo **********_Cleaning_dirs_and_files_**********
#	rm -rf ${DIR_BIN}
	rm -f *.o
	rm -f *.so
	rm -f ${OUT_GUI}
	@echo **********_Cleaned_**********
