cmake_minimum_required(VERSION 3.24)
project(Group_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Data)

add_executable(Group_Project
        Data/Houses.csv
        Data/Members.csv
        Admin.cpp
        Admin.h
        Data.cpp
        Data.h
        Guest.cpp
        Guest.h
        House.cpp
        House.h
        main.cpp
        Member.cpp
        Member.h)
