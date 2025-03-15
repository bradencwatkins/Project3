cmake_minimum_required(VERSION 3.28)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab2 main.cpp
        Token.h
        Parser.h
        Scanner.h
        Predicate.h
        Parameter.h
        Rule.h
        Datalog.h
        Scheme.h
        Tuple.h
        Relation.h
        Relation.h
        Interpreter.h
        Database.h
)
