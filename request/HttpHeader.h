#ifndef HTTP_SERVER_HTTPHEADER_H
#define HTTP_SERVER_HTTPHEADER_H
#include "../routes/HttpMethod.h"

struct HttpHeader {
    HttpMethod method;
    std::string uri;
    std::string version;

    public:
        HttpHeader(std::string_view header);
};

#endif //HTTP_SERVER_HTTPHEADER_H
