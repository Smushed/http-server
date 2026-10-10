#ifndef HTTP_SERVER_HTTPMETHOD_H
#define HTTP_SERVER_HTTPMETHOD_H
#include <string_view>
#include <sstream>

enum class HttpMethod {
    GET,
    PUT,
    POST,
    DELETE
};

constexpr HttpMethod textToHttpMethod(const std::string_view method) {
    using enum HttpMethod;
    if (method == "GET") return GET;
    if (method == "PUT") return PUT;
    if (method == "POST") return POST;
    if (method == "DELETE") return DELETE;
    throw std::invalid_argument("Invalid HTTP Method");
}

constexpr std::string_view getTextFromHttpMethod(const HttpMethod method) {
    using enum HttpMethod;
    switch (method) {
        case GET: return "GET";
        case PUT: return "PUT";
        case POST: return "POST";
        case DELETE: return "DELETE";
        default: throw std::invalid_argument("Invalid HTTP Method");
    }
}

#endif //HTTP_SERVER_HTTPMETHOD_H
