#ifndef HTTP_SERVER_HTTPRESPONSE_H
#define HTTP_SERVER_HTTPRESPONSE_H
#include <string>
#include <vector>

struct HttpResponse {
    HttpResponse()=default;
    HttpResponse(std::string_view version, int statusCode, std::string_view message, std::string_view body);
    HttpResponse(std::string_view version, int statusCode, std::string_view message, const std::vector<char>& data);
    HttpResponse(std::string_view version);

    void build(std::string_view version, int statusCode, std::string_view message, std::string_view body);
    void build(std::string_view version, int statusCode, std::string_view message, const std::vector<char>& data);
    void updateWithResult(int statusCode, std::string_view message, std::string_view body);
    void updateWithResult(int statusCode, std::string_view message, const std::vector<char>& data);

    void sendResponse(int socket, int flags) const;
    private:
        std::string m_version;
        int m_statusCode{};
        std::string m_message;
        std::string m_body;
        std::vector<char> m_data;
};


#endif //HTTP_SERVER_HTTPRESPONSE_H
