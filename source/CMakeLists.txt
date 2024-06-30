cmake_minimum_required(VERSION 3.12)

project(matrix_prj)

set(main_files 
main.cpp 
matrix.h matrix.ipp
)

add_executable(matrix ${main_files})

if(MSVC)
	    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT matrix)
        source_group("Main" FILES ${main_files})
endif ()


target_compile_options(matrix PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX >
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>
        )

set_target_properties(matrix PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

