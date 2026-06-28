#ifndef HTTP_SERVER_HTTPMETHOD_H
#define HTTP_SERVER_HTTPMETHOD_H
#include <string_view>

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
}

constexpr std::string_view getHttpMethodFromText(const HttpMethod method) {
    using enum HttpMethod;
    switch (method) {
        case GET: return "GET";
        case PUT: return "PUT";
        case POST: return "POST";
        case DELETE: return "DELETE";
    }
}

#endif //HTTP_SERVER_HTTPMETHOD_H
