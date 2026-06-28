#ifndef HTTP_SERVER_HTTPREQUEST_H
#define HTTP_SERVER_HTTPREQUEST_H
#include <string_view>
#include "../routes/HttpMethod.h"


class HttpRequest {
    public:
        HttpMethod getMethod() const { return m_method; }
        HttpRequest(std::string_view connectionString);
    private:
        HttpMethod m_method{};

};


#endif //HTTP_SERVER_HTTPREQUEST_H
