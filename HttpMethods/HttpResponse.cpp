#include "HttpResponse.h"

#include <iostream>
#include <sys/socket.h>

constexpr int defaultResponseSize() { return 57; }
constexpr std::string spacer() { return "\r\n"; }
constexpr std::string contentTypeText() { return "Content-Type: text/plain"; }
constexpr std::string contentLength() { return "Content-Length: "; }

HttpResponse::HttpResponse(const std::string_view version, const int statusCode, std::string_view message, std::string_view body)
    :   m_version{version},
        m_statusCode{statusCode},
        m_message{message},
        m_body{body}
{}

HttpResponse::HttpResponse(const std::string_view version, const int statusCode, const std::string_view message, const std::vector<char>& data)
    :   m_version{version},
        m_statusCode{statusCode},
        m_message{message},
        m_data{data}
{}

HttpResponse::HttpResponse(const std::string_view version)
    :   m_version{version}
{}

void HttpResponse::build(const std::string_view version, const int statusCode, const std::string_view message, const std::string_view body) {
    this->m_version = version;
    this->m_statusCode = statusCode;
    this->m_message = message;
    this->m_body = body;
    this->m_data = std::vector<char>();
}

void HttpResponse::updateWithResult(const int statusCode, const std::string_view message, const std::string_view body) {
    this->m_statusCode = statusCode;
    this->m_message = message;
    this->m_body = body;
    this->m_data = std::vector<char>();
}

void HttpResponse::build(const std::string_view version, const int statusCode, const std::string_view message, const std::vector<char>& data) {
    this->m_version = version;
    this->m_statusCode = statusCode;
    this->m_message = message;
    this->m_body = "";
    this->m_data = data;
}

void HttpResponse::updateWithResult(const int statusCode, const std::string_view message, const std::vector<char>& data) {
    this->m_statusCode = statusCode;
    this->m_message = message;
    this->m_body = "";
    this->m_data = data;
}

void HttpResponse::sendResponse(const int socket, const int flags) const {

    std::string responseBuffer {};
    const unsigned long bodySize { this->m_body.size() };
    responseBuffer.reserve(this->m_version.size() + bodySize + defaultResponseSize());

    responseBuffer.append(m_version);
    responseBuffer.append(" ");
    responseBuffer.append(m_body);
    responseBuffer.append(spacer());
    responseBuffer.append(contentTypeText());
    responseBuffer.append(spacer());
    responseBuffer.append(contentLength());
    responseBuffer.append(std::to_string(bodySize));
    responseBuffer.append(spacer());
    responseBuffer.append(spacer());
    responseBuffer.append(m_body);

    const char* ptr = responseBuffer.data();
    size_t bytesLeft = responseBuffer.size();

    while (bytesLeft > 0) {
        const long bytesSent = send(socket, ptr, bytesLeft, flags);
        if (bytesSent == -1) {
            std::cout << "Error in sending response to client" << std::endl;
            throw std::runtime_error("Error sending response");
        }
        ptr += bytesSent;
        bytesLeft -= bytesSent;
    }
}
