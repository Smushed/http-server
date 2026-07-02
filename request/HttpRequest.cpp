#include "HttpRequest.h"
#include <sstream>
#include "HttpHeader.h"

HttpRequest::HttpRequest(const std::string_view connectionString) : header(connectionString) {
    this->header = HttpHeader(connectionString);
}
