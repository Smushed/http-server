#ifndef HTTP_SERVER_HTTPREQUEST_H
#define HTTP_SERVER_HTTPREQUEST_H
#include <string_view>

#include "HttpHeader.h"
#include "../HttpMethod.h"


class HttpRequest {
    public:
        HttpMethod getMethod() const { return header.method; }
        HttpRequest(std::string_view connectionString);
        void processRequest();
    private:
        HttpHeader header;
};


#endif //HTTP_SERVER_HTTPREQUEST_H
