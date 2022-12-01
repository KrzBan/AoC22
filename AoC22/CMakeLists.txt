# CMakeList.txt : CMake project for AoC22, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (AoC22 "AoC22.cpp" "AoC22.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AoC22 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
