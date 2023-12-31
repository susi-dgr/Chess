cmake_minimum_required(VERSION 3.21)
project(Danninger-Susanne-Chess)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) # enable virtual folders for projects if supported by the build system/IDE

# set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/static)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# logic for packaging
install(DIRECTORY ../doc DESTINATION . OPTIONAL)
install(DIRECTORY ../src DESTINATION .)
set(CPACK_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME})
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP")
include(CPack)

# configure C17
set(CMAKE_C_STANDARD 17)          # request C17
set(CMAKE_C_STANDARD_REQUIRED ON) # enforce requested standard
set(CMAKE_C_EXTENSIONS OFF)       # disable compiler specific extensions

# configure C++20
set(CMAKE_CXX_STANDARD 20)          # request C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON) # enforce requested standard
set(CMAKE_CXX_EXTENSIONS OFF)       # disable compiler specific extensions

# helper function to simplify definition of projects
function(target name)
	file(GLOB_RECURSE SRC "${name}/*")   # recursively collect all files in sub-folder for project
	add_executable(${name} ${SRC})       # define project "name" based on files found in SRC

	#set required warning flags
	if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU"   OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	   "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		target_compile_options(${name} PRIVATE
			-Wall        # enable "all" warnings
			-Wextra      # enable extra warnings
			-Wpedantic   # enable strict conformance warnings
			-Wconversion # enable warnings for dangerous implicit conversions
			-Werror=vla  # disable support for VLAs
		)
		target_link_libraries(${name} PRIVATE
			m # math library must be explicitly linked on Unix
		)
	elseif("${CMAKE_C_COMPILER_ID}" STREQUAL "MSVC" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
		target_compile_options(${name} PRIVATE
			/W4          # enable almost all "necessary" warnings
			/permissive- # enforce strict standard compliance
			/JMC         # optimize debugging experience
			/MP          # enable parallel compilation
		)
	else()
		message(WARNING "unknown compiler, no warning flags set!")
	endif()
endfunction()

target(chess)