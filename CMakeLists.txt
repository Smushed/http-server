cmake_minimum_required(VERSION 4.2)
project(http_server)

set(CMAKE_CXX_STANDARD 26)

add_executable(http_server main.cpp
        Server.cpp
        Server.h
        request/HttpRequest.cpp
        request/HttpRequest.h
        HttpMethod.h
        request/HttpHeader.cpp
        request/HttpHeader.h
        routes/gets/Index.cpp
        routes/gets/Index.h
        routes/Router.cpp
        routes/Router.h
        routes/Route.cpp
        routes/Route.h
)
