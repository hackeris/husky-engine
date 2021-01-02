cmake_minimum_required(VERSION 3.17)
project(husky_compute)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
add_executable(husky_compute
        grammar/HuskyLangParser.cpp
        grammar/HuskyLangLexer.cpp
        grammar/HuskyLangBaseVisitor.cpp
        grammar/HuskyLangVisitor.cpp
        main.cpp lang/GraphCompiler.cpp
        lang/GraphCompiler.h
        lang/Graph.h
        runtime/GraphVM.cpp
        runtime/GraphVM.h
        runtime/ValueBase.h runtime/Runtime.cpp runtime/Runtime.h dal/DataRepository.cpp dal/DataRepository.h runtime/lib/Function.h
        runtime/lib/Function.cpp)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

target_include_directories(husky_compute PUBLIC
        /usr/local/include/antlr4-runtime
        /usr/local/opt/mysql-connector-c++/include)
target_link_directories(husky_compute PUBLIC
        /usr/local/lib
        /usr/local/opt/mysql-connector-c++/lib)
target_link_libraries(husky_compute
        antlr4-runtime
        cpprestsdk::cpprest
        mysqlcppconn8)
