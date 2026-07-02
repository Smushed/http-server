#ifndef HTTP_SERVER_HTTPREQUEST_H
#define HTTP_SERVER_HTTPREQUEST_H
#include <string_view>

#include "HttpHeader.h"
#include "../HttpMethod.h"


class HttpRequest {
    public:
        HttpMethod getMethod() const { return header.method; }
        HttpRequest(std::string_view connectionString);
    private:
        HttpHeader header;
        std::string version;
};


#endif //HTTP_SERVER_HTTPREQUEST_H
