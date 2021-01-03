cmake_minimum_required(VERSION 3.17)
project(husky_engine)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
add_executable(husky_engine
        grammar/HuskyLangParser.cpp
        grammar/HuskyLangLexer.cpp
        grammar/HuskyLangBaseVisitor.cpp
        grammar/HuskyLangVisitor.cpp
        main.cpp lang/graph_compiler.cpp
        lang/graph_compiler.h
        lang/graph.h
        runtime/graph_vm.cpp
        runtime/graph_vm.h
        runtime/value_base.h
        runtime/runtime.cpp runtime/runtime.h dal/data_repository.cpp dal/data_repository.h runtime/lib/func.h
        runtime/lib/func.cpp api/controller.cpp api/controller.h api/router.cpp api/router.h util/timer.h)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

target_include_directories(husky_engine PUBLIC
        /usr/local/include/antlr4-runtime
        /usr/local/opt/openssl/include
        /usr/local/opt/mysql-connector-c++/include)
target_link_directories(husky_engine PUBLIC
        /usr/local/lib
        /usr/local/opt/openssl/lib
        /usr/local/opt/mysql-connector-c++/lib)
target_link_libraries(husky_engine
        antlr4-runtime
        ssl crypto
        cpprestsdk::cpprest
        mysqlcppconn8)
