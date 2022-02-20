cmake_minimum_required(VERSION 3.0)

# Paths to GUI application
set(DIR_AMADINA_WIDGETS 	"widgets/")
set(DIR_AMADINA_MENU 		"menu/")
set(DIR_WXBIND 				"../wx_binding/")
set(DIR_KERNEL 				"../kernel/")

add_executable(amadina "")
target_link_libraries(amadina amadina_wx)
target_link_options(amadina PRIVATE -mwindows)
target_include_directories(amadina PRIVATE ${WX_WIDGETS_INCLUDE})
target_include_directories(amadina PRIVATE ${WX_WIDGETS_SETUP})
target_include_directories(amadina PRIVATE ${DIR_WXBIND})
target_include_directories(amadina PRIVATE ${DIR_KERNEL})

target_sources(amadina
		PRIVATE 
			amadin_app.cpp
			main_frame.cpp
			wxchoicelayer.cpp
			${DIR_AMADINA_WIDGETS}toolbar_items.cpp
			${DIR_AMADINA_WIDGETS}console/uiconsole.cpp
			${DIR_AMADINA_MENU}menu.cpp
)