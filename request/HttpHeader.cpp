#include "HttpHeader.h"

#include <iostream>
#include <sstream>

HttpHeader::HttpHeader(const std::string_view header) {
    std::stringstream ss(header);
    std::string parsedVal {};
    int i {0};

    constexpr int METHOD_POSITION {0};
    constexpr int URI_POSITION {1};
    constexpr int VERSION_POSITION {2};
    while (ss >> parsedVal) {
        if (i == METHOD_POSITION) {
            this->method = textToHttpMethod(parsedVal);
        }
        if (i == URI_POSITION) {
            this->uri = parsedVal;
        }
        if (i == VERSION_POSITION) {
            this->version = parsedVal;
        }
        if (i > VERSION_POSITION) {
            break;
        }
        i++;
    }
}
