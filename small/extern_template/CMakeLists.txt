project (ExternTemplate)
cmake_minimum_required(VERSION 2.6)

# set( CMAKE_CXX_FLAGS "-DFOOBAR" )
    
ADD_DEFINITIONS(
	-Wall
	-pedantic
	-march=nocona
	-O2
)

add_executable ( extern_template
	main.cpp
	rect.cpp
)
