cmake_minimum_required(VERSION 3.21)

project(MenuPlay)

add_compile_definitions(WIN_ENV=1)
add_compile_definitions(_WINDOWS=1)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_compile_definitions(MENUPLAY_LIBRARY)

add_library(${PROJECT_NAME} SHARED)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".aip")

target_sources(${PROJECT_NAME} PRIVATE
    "Source/MenuPlaySuites.h"
    "Source/MenuPlaySuites.cpp"
    "Source/MenuPlayID.h"
	"Source/MenuPlayPlugin.h"	
        "Source/MenuPlayPlugin.cpp"

	"../common/source/Main.cpp"
	"../common/source/Plugin.cpp"
	"../common/source/SDKAboutPluginsHelper.cpp"
	"../common/source/Suites.cpp"	
        "../common/source/IllustratorSDK.cpp"
        "../common/includes/IllustratorSDK.h"
        "../common/source/FlashUIController.cpp"
        "../common/source/SDKPlugPlug.cpp"
        "../common/source/SDKErrors.cpp"
        "../common/source/AppContext.cpp"
        "Resources/Win/MenuPlay.rc"

        "../../illustratorapi/illustrator/AIAssert.cpp"
#       "../../illustratorapi/illustrator/IAIArtboards.cpp"
#        "../../illustratorapi/ate/IText.cpp"
        "../../illustratorapi/ate/IThrowException.cpp"
       "../../illustratorapi/illustrator/IAIFilePath.cpp"
 #       "../../illustratorapi/illustrator/IAIStringFormatUtils.cpp"
     "../../illustratorapi/illustrator/IAIUnicodeString.cpp"

    	
)

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Source>)

target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../common/includes>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../common/win>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/pica_sp>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/illustrator>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/ate>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/ate/slotextdomtypes>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/ate/legacy>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/illustrator/config>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/illustrator/config/compiler>)
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../../illustratorapi/illustrator/actions>)

target_precompile_headers(${PROJECT_NAME}
  PUBLIC
    ../common/includes/IllustratorSDK.h
)

set_source_files_properties(MenuPlay.rc PROPERTIES LANGUAGE RC)

foreach(LANG  C CXX RC)
    set(CMAKE_${LANG}_STANDARD_INCLUDE_DIRECTORIES ${CUSTOM_INCLUDE_DIRECTORIES})
endforeach()




