cmake_minimum_required(VERSION 3.20)
project(2021_fall_project_group_e_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(Code)

add_executable(2021_fall_project_group_e_1
        Code/Admin.cpp
        Code/Admin.h
        Code/Locations.cpp
        Code/Locations.h
        Code/main.cpp
        Code/Paths.cpp
        Code/Paths.h
        Code/User.h
        Code/userlogin.h
        Code/LinkedList.h
        Code/List.h)
