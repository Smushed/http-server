#include "HttpHeader.h"

#include <iostream>
#include <sstream>

HttpHeader::HttpHeader(std::string_view header) {
    std::stringstream ss(header);
    std::string parsedVal {};

    constexpr int METHOD_POSITION {0};
    constexpr int URL_POSITION {1};
    constexpr int VERSION_POSITION {2};
    for (int i = 0; i <= VERSION_POSITION; i++) {
        if (i == METHOD_POSITION) {
            this->method = textToHttpMethod(parsedVal);
        } else if (i == URL_POSITION) {
            ss >> this->uri;
        } else if (i == VERSION_POSITION) {
            ss >> this->version;
        }
    }
    // while (ss >> parsedVal) {
    //     if ()
    //     std::cout << parsedVal << std::endl;
    // }
    // this->method =
}
