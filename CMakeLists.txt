cmake_minimum_required(VERSION 2.8)
set(CMAKE_SUPPRESS_REGENERATION true)
project(radon-transform-mk2)

file(GLOB my_source_files "*.h" "*.cpp" "*.cxx")
add_executable(radon-transform-mk2 ${my_source_files} )  

#Adds OpenGL
find_package(OpenGL)
target_link_libraries(radon-transform-mk2 ${OPENGL_LIBRARIES})

#Adds ITK
set(ITK_DIR "C:/lib/InsightToolkit-4.8.1-64")
find_package(ITK REQUIRED)
target_link_libraries(radon-transform-mk2  ${ITK_LIBRARIES})
#Adds GLEW
add_subdirectory(C:/lib/glfw binary_dir)
include_directories(C:/lib/glfw)
target_link_libraries(radon-transform-mk2 glfw ${GLFW_LIBRARIES})
#Adds GLEW
include_directories(C:/lib/glew-2.0.0/include)
target_link_libraries(radon-transform-mk2 C:/lib/glew-2.0.0/lib/Release/x64/glew32.lib)

#suprime o warning chato dos infernos que a ITK gera por usar funções inseguras da api do windows
add_definitions(-D_SCL_SECURE_NO_WARNINGS)


