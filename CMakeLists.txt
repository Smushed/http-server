cmake_minimum_required(VERSION 4.2)
project(http_server)

set(CMAKE_CXX_STANDARD 26)

add_executable(http_server main.cpp
        Listener.cpp
        Listener.h
        request/HttpRequest.cpp
        request/HttpRequest.h
        routes/HttpMethod.h
)
