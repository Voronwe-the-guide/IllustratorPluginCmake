# IllustratorPluginCmake
A test to port an Adobe Illustrator Plugin to Cmake


This is a try to port the MenuPlay from the Adobe Illustrator SDK Samples to CMake in Windows

The Cmake-file can be found in sampleCode/MenuPlay

The Illustrator API itself is not included, because I was unclear whether it is ok to do so. Add the folder "illustratorapi" to the main-folder

The plugin has to be build as a dll. Internally, an additional .lib has to be created. This is done by calling 
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    
in CMake
