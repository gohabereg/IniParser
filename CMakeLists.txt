cmake_minimum_required(VERSION 3.8)
project(Test)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp headers/IniParser.h src/IniParser.cpp src/FileIOException.cpp headers/FileIOException.h src/ParseException.cpp headers/ParseException.h src/IniParserException.cpp headers/IniParserException.h)
add_executable(Test ${SOURCE_FILES})