#include "HttpRequest.h"

#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

#include "HttpHeader.h"

HttpRequest::HttpRequest(std::string_view connectionString) {
    // std::cout << connectionString << std::flush;
    // std::cout << connectionString << "\n------------------\n" << std::endl;

    // Safe log check: Strip out or replace '\r' so it doesn't break the terminal cursor
    // std::string cleanLog = connectionString.data();
    // size_t pos;

    HttpHeader header(connectionString);

    // std::vector<std::string> splitRequest;
    // std::stringstream ss(connectionString);
    // std::string temp;
    // while (std::getline(ss, temp, '\n')) {
    //     std::cout << temp << std::endl;
    //     splitRequest.push_back(temp);
    // }
    //
    // for (int i = 0; i < splitRequest.size(); i++) {
    //     std::cout << splitRequest.at(i) << std::endl;
    // }
    //
    // std::cout << "--- RAW REQUEST ---" << std::endl;
    // std::cout << cleanLog << std::endl;
}
