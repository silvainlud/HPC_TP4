cmake_minimum_required(VERSION 3.21)
project(TP4)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(RayTracing)

add_executable(TP4 hpcOpenmpSchedule.cpp)
add_executable(TP4_EX2 ex2.cpp)
add_definitions(-O2)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(TP4 PUBLIC OpenMP::OpenMP_CXX)
    target_link_libraries(TP4_EX2 PUBLIC OpenMP::OpenMP_CXX)

endif()