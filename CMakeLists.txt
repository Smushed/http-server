cmake_minimum_required(VERSION 4.2)
project(http_server)

set(CMAKE_CXX_STANDARD 26)

add_executable(http_server main.cpp
        Server.cpp
        Server.h
        HttpMethods/HttpRequest.cpp
        HttpMethods/HttpRequest.h
        HttpMethod.h
        HttpMethods/HttpHeader.cpp
        HttpMethods/HttpHeader.h
        routes/gets/Index.cpp
        routes/gets/Index.h
        routes/Router.cpp
        routes/Router.h
        routes/Route.cpp
        routes/Route.h
        routes/StatusCodes.h
        HttpMethods/HttpResponse.cpp
        HttpMethods/HttpResponse.h
)
