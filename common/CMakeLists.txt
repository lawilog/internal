cmake_minimum_required(VERSION 2.6)
project(common)

add_definitions(-Wall -std=c++0x -O2)

add_executable(extract_block
	extract_block.cpp
	TableFile.cpp
	LineArray.cpp
)

add_executable(interval_unite
	interval_unite.cpp
#	LineArray.cpp
)

add_executable(dat_cross
	dat_cross.cpp
	TableFile.cpp
	LineArray.cpp
)

add_executable(LineArray_testcase
	LineArray_testcase.cpp
	LineArray.cpp
)

add_executable(implode_explode_testcase
	implode_explode_testcase.cpp
	implode_explode.cpp
)

add_executable(TableFile_testcase
	TableFile_testcase.cpp
	TableFile.cpp
	LineArray.cpp
)

add_executable(parse_testcase
	parse_testcase.cpp
)
