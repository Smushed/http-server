#include "Index.h"
#include <iostream>
#include <sstream>
#include "../../HttpMethods/HttpResponse.h"

std::string Index::servePage(HttpResponse& response) {
    const std::ifstream indexHtml ("/home/smushed/Coding/http-server/assets", std::ios::in | std::ios::binary);
    if (!indexHtml.is_open()) {
        std::cout << "Error opening index.html" << std::endl;
        throw std::runtime_error("Error opening index.html");
    }
    std::stringstream ss;
    ss << indexHtml.rdbuf();
    std::cout << ss.str() << std::endl;
    response.updateWithResult(200, "Success", ss.str());
    return ss.str();
}
