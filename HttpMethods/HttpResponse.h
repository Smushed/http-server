#ifndef HTTP_SERVER_HTTPRESPONSE_H
#define HTTP_SERVER_HTTPRESPONSE_H
#include <string>
#include <vector>

struct HttpResponse {
    HttpResponse()=default;
    HttpResponse(int version, int statusCode, std::string message, std::string body);
    HttpResponse(int version, int statusCode, std::string message, std::vector<char> data);
    void buildResponse(int version, int statusCode, std::string message, std::string body);
    void buildResponse(int version, int statusCode, std::string message, std::vector<char> data);
    private:
        int m_version;
        int m_statusCode;
        std::string m_message;
        std::string m_body;
        std::vector<char> m_data;
};


#endif //HTTP_SERVER_HTTPRESPONSE_H
