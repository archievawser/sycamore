cmake_minimum_required (VERSION 3.8)

project ("sycamore")

# Output a static library
add_library (sycamore STATIC "src/Main.cpp"  "include/Core.h" )

# Use C++20
set_property(TARGET sycamore PROPERTY CXX_STANDARD 20)

# Setup include & library directories
target_include_directories(sycamore PUBLIC "./include/")
target_link_directories(sycamore PUBLIC "./lib/")

# Optionally build examples
option(BUILD_EXAMPLES "Whether or not example executives should be built" false)

if(BUILD_EXAMPLES)
	project ("examples")

	add_executable(examples "examples/HelloCube/Main.cpp" )
	target_include_directories(examples PUBLIC "./include/")
endif()