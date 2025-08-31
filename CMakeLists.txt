cmake_minimum_required(VERSION 3.10)
project(Cpp_OOP_example)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
main.cpp 
AbstrEmp.cpp 
Service.cpp
AbstrEmp.h
Service.h)