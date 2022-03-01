cmake_minimum_required(VERSION 3.18)
project(TP4)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(Exercice_3)

add_executable(TP4_EX1 Exercice_1/hpcOpenmpSchedule.cpp)
add_executable(TP4_EX2 Exercice_2/ex2.cpp)
add_definitions(-O2)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(TP4_EX1 PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(TP4_EX2 PUBLIC OpenMP::OpenMP_CXX)

endif()