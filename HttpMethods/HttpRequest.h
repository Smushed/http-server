#ifndef HTTP_SERVER_HTTPREQUEST_H
#define HTTP_SERVER_HTTPREQUEST_H
#include <string_view>

#include "HttpHeader.h"
#include "../HttpMethod.h"


class HttpRequest {
    public:
        HttpMethod getMethod() const { return m_header.method; }
        std::string& getURI() { return m_header.uri; }
        std::string& getVersion() { return m_header.version; }
        HttpRequest(std::string_view connectionString);
    private:
        HttpHeader m_header;
        std::string m_version;
};


#endif //HTTP_SERVER_HTTPREQUEST_H
