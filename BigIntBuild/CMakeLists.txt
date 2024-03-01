cmake_minimum_required(VERSION 3.28.3)

project(test)

include_directories(C:/Users/ae/BigIntBuild/include)
add_executable(testname
	include/BigInt.h
	include/BigInt.cpp
	src/bTest.cpp)