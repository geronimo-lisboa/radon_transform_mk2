cmake_minimum_required(VERSION 2.8)
set(CMAKE_SUPPRESS_REGENERATION true)
project(radon-transform-mk2)

#set(VTK_DIR "C:/lib/VTK-7.1.1/VTK-7.1.1")
set(ITK_DIR "C:/lib/InsightToolkit-4.8.1-64")
# Find VTK
#find_package(VTK REQUIRED)
#include(${VTK_USE_FILE})
# Find ITK
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

file(GLOB my_source_files "*.h" "*.cpp" "*.cxx")
add_executable(radon-transform-mk2 ${my_source_files} )  
#bota vtk e ITK
target_link_libraries(radon-transform-mk2   ${ITK_LIBRARIES})


#suprime o warning chato dos infernos que a ITK gera por usar funções inseguras da api do windows
add_definitions(-D_SCL_SECURE_NO_WARNINGS)



