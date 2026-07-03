#include "HttpRequest.h"
#include <sstream>
#include "HttpHeader.h"

HttpRequest::HttpRequest(const std::string_view connectionString) : m_header(connectionString) {
    this->m_header = HttpHeader(connectionString);
}
