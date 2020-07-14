cmake_minimum_required(VERSION 3.1)
project(rayfork-tests LANGUAGES C CXX)

# Set ASSETS_PATH define
if (NOT DEFINED ASSETS_PATH)
	add_compile_definitions(ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
endif()

# Set path variables
set(rayfork_path "${CMAKE_SOURCE_DIR}/source/")
set(platform_header_path "${CMAKE_SOURCE_DIR}/tests/platform-independent-tests/platform-layers/")

# Add sokol examples
add_subdirectory(platform-independent-tests/platform-layers/sokol)       # Add the sokol platform layer
file(GLOB files "platform-independent-tests/tests/*.c")                  # Create an iterable with all the filenames in examples/
foreach(file ${files})                                                   # Iterate over all files
	get_filename_component(name ${file} NAME_WE)                         # Create a variable `name` that stores the filename without the extension. NAME_WE means filename with extension. (https://cmake.org/cmake/help/v3.0/command/get_filename_component.html).
	add_executable(${name})                                     		 # Create the target for the specific example
	target_sources(${name} PRIVATE ${file})				    			 # Add sources to target
	target_link_libraries(${name} PRIVATE sokol-platform-layer rayfork)  # Link with the platform layer and rayfork
	target_include_directories(${name} PUBLIC platform-independent-tests/platform-layers/) # Add platform.h to the include path
endforeach()

# Setup unit-tests
add_executable(unit-test-suite)
target_sources(unit-test-suite PRIVATE unit-tests/tests.cpp)
target_link_libraries(unit-test-suite PRIVATE rayfork)
target_compile_features(unit-test-suite PUBLIC cxx_std_17)
set_target_properties(unit-test-suite PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
target_include_directories(unit-test-suite PRIVATE "libs")