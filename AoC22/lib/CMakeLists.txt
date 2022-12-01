# CMakeList.txt : CMake project for AoC22, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (AoC22Lib)

target_sources(AoC22Lib PRIVATE "d1/d1.h" "d1/d1.cpp" "common.h")
target_include_directories(AoC22Lib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file("inputs/input01.txt" "inputs/input01.txt" COPYONLY)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AoC22Lib PROPERTY CXX_STANDARD 20)
endif()