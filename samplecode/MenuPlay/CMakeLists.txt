cmake_minimum_required(VERSION 3.14)


project(MenuPlay)


add_compile_definitions(WIN_ENV=1)

#set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME})
add_library(${PROJECT_NAME}::${PROJECT_NAME}  ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".aip")

target_sources(${PROJECT_NAME} PRIVATE
	"Source/MenuPlayID.h"
	"Source/MenuPlayPlugin.h"	
        "Source/MenuPlayPlugin.cpp"
        "Source/MenuPlaySuites.h"
        "Source/MenuPlaySuites.cpp"
	"../common/source/Main.cpp"
	"../common/source/Plugin.cpp"
	"../common/source/SDKAboutPluginsHelper.cpp"
	"../common/source/Suites.cpp"	
	"Resources/Win/MenuPlay.rc"
    	
)

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Source>)

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../common/includes>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../common/win>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/pica_sp>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/illustrator>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/ate>)


foreach(LANG  C CXX RC)
    set(CMAKE_${LANG}_STANDARD_INCLUDE_DIRECTORIES ${CUSTOM_INCLUDE_DIRECTORIES})
endforeach()


