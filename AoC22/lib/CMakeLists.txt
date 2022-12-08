# CMakeList.txt : CMake project for AoC22, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (AoC22Lib)

target_sources(AoC22Lib PRIVATE 
	"common.h" 
	"d1/d1.h"	"d1/d1.cpp" 
	"d2/d2.h"	"d2/d2.cpp" 
	"d3/d3.cpp" "d3/d3.h"
	"d4/d4.cpp" "d4/d4.h"
	"d5/d5.cpp" "d5/d5.h"
	"d6/d6.cpp" "d6/d6.h"
	"d7/d7.cpp" "d7/d7.h" 
	"d8/d8.cpp" "d8/d8.h")
target_include_directories(AoC22Lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file("inputs/input01.txt" "inputs/input01.txt" COPYONLY)
configure_file("inputs/input02.txt" "inputs/input02.txt" COPYONLY)
configure_file("inputs/input03.txt" "inputs/input03.txt" COPYONLY)
configure_file("inputs/input04.txt" "inputs/input04.txt" COPYONLY)
configure_file("inputs/input05.txt" "inputs/input05.txt" COPYONLY)
configure_file("inputs/input06.txt" "inputs/input06.txt" COPYONLY)
configure_file("inputs/input07.txt" "inputs/input07.txt" COPYONLY)
configure_file("inputs/input08.txt" "inputs/input08.txt" COPYONLY)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AoC22Lib PROPERTY CXX_STANDARD 20)
endif()