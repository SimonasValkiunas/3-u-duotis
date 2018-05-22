cmake_minimum_required(VERSION 3.10)
project(OOP_3)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(OOP_3
        funkcijosGeneravimas.cpp
        main.cpp
        StudentoKlase.cpp
        StudentoKlase.h
        )

 add_executable(Testai
       testCases/test.cpp
       funkcijosGeneravimas.cpp
       StudentoKlase.cpp
       StudentoKlase.h
      )
