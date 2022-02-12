cmake_minimum_required(VERSION 3.0)

# Paths to wx-binding translation units
set(DIR_WXBIND_CLASSES 	"classes/")
set(DIR_WXBIND_RES 		"res/")
set(DIR_WXBIND_SRC 		"src/")
set(DIR_KERNEL 			"../kernel/")

add_library(amadina_wx SHARED "")

target_include_directories(amadina_wx PRIVATE ${WX_WIDGETS_INCLUDE})
target_include_directories(amadina_wx PRIVATE ${WX_WIDGETS_SETUP})
target_include_directories(amadina_wx PRIVATE ${DIR_KERNEL})

target_link_libraries(amadina_wx amadina_kernel)
file(GLOB WX_LIBS ${WX_WIDGETS_LIB}/*.a)
target_link_libraries(amadina_wx ${WX_LIBS})

target_sources(amadina_wx
		PRIVATE 
			${DIR_WXBIND_CLASSES}dcadapter_wx.cpp
			${DIR_WXBIND_CLASSES}events.cpp
			${DIR_WXBIND_CLASSES}viewpanel.cpp
)

target_sources(amadina_wx
		PRIVATE 
			${DIR_WXBIND_RES}provider.cpp
)

target_sources(amadina_wx
		PRIVATE 
			${DIR_WXBIND_SRC}wx_objects.cpp
			${DIR_WXBIND_SRC}wx_binding.cpp
)

