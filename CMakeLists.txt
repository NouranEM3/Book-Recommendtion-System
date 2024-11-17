cmake_minimum_required(VERSION 3.27)
project(P1)

set(CMAKE_CXX_STANDARD 17)

add_executable(P1 p1.cpp
        RatingList.h
        BookList.cpp
        MemberList.cpp
        RatingList.cpp)
