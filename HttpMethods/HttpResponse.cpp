#include "HttpResponse.h"

HttpResponse::HttpResponse(int version, int statusCode, std::string message, std::string body)
    :   m_version(version),
        m_statusCode(statusCode),
        m_message(std::move(message)),
        m_body(std::move(body)),
        m_data({})
{}

HttpResponse::HttpResponse(int version, int statusCode, std::string message, std::vector<char> data)
    :   m_version(version),
        m_statusCode(statusCode),
        m_message(std::move(message)),
        m_body({}),
        m_data(std::move(data))
{}

void HttpResponse::buildResponse(int version, int statusCode, std::string message, std::string body) {
    this->m_version = version;
    this->m_statusCode = statusCode;
    this->m_message = std::move(message);
    this->m_body = std::move(body);
    this->m_data = std::vector<char>();
}

void HttpResponse::buildResponse(int version, int statusCode, std::string message, std::vector<char> data) {
    this->m_version = version;
    this->m_statusCode = statusCode;
    this->m_message = std::move(message);
    this->m_body = "";
    this->m_data = data;
}