#include "HttpRequest.h"

#include <iostream>
#include <ostream>

HttpRequest::HttpRequest(std::string_view connectionString) {
    // std::cout << connectionString << std::flush;
    // std::cout << connectionString << "\n------------------\n" << std::endl;

    // Safe log check: Strip out or replace '\r' so it doesn't break the terminal cursor
    std::string cleanLog = connectionString.data();
    size_t pos;
    while ((pos = cleanLog.find('\r')) != std::string::npos) {
        cleanLog.replace(pos, 1, "[R]"); // Replace raw carriage returns with text
    }

    std::cout << "--- RAW REQUEST ---" << std::endl;
    std::cout << cleanLog << std::endl;
}
