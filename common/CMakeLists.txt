cmake_minimum_required(VERSION 2.6)
project(common)

add_definitions(-Wall -Wno-unused-local-typedefs -std=c++0x -O2)

include_directories("/usr/include/eigen3")
include_directories("$ENV{HOME}/proggen/common")

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

add_executable(explode_parse_testcase
	explode_parse_testcase.cpp
	implode_explode.cpp
)

add_executable(TableFile_testcase
	TableFile_testcase.cpp
	TableFile.cpp
	LineArray.cpp
)

add_executable(align_as_table
	align_as_table.cpp
	LineArray.cpp
)


# add_executable(buffer_test buffer_test.cpp)
add_executable(cout_vector_test cout_vector_test.cpp)
add_executable(parse_testcase parse_testcase.cpp)
add_executable(RandDistrib_testcase RandDistrib_testcase.cpp)
add_executable(stringprintf stringprintf.cpp)
add_executable(FunInterpolTable_testcase FunInterpolTable_testcase.cpp)
add_executable(bytes2str_testcase bytes2str_testcase.cpp)
add_executable(EigenOctave_testcase EigenOctave_testcase.cpp)
add_executable(lsqnonneg_test lsqnonneg_test.cpp)
add_executable(lscov_testcase lscov_testcase.cpp)
