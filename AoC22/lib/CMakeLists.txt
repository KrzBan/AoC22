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
	"d8/d8.cpp" "d8/d8.h" 
	"d9/d9.cpp" "d9/d9.h" 
	"d10/d10.h" "d10/d10.cpp"
	"d11/d11.h" "d11/d11.cpp"
	"d12/d12.h" "d12/d12.cpp"
)
target_include_directories(AoC22Lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(copy_inputs
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/inputs ${CMAKE_CURRENT_BINARY_DIR}/inputs
)
add_dependencies(AoC22Lib copy_inputs)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AoC22Lib PROPERTY CXX_STANDARD 20)
endif()