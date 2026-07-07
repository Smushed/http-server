#include "Index.h"
#include <iostream>
#include <sstream>
#include "../../HttpMethods/HttpResponse.h"

std::string readFile(std::string_view path) {
    constexpr auto read_size = std::size_t(4096);
    auto stream = std::ifstream(path.data());
    stream.exceptions(std::ios_base::badbit);

    if (not stream) {
        throw std::ios_base::failure("file does not exist");
    }

    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(& buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

void Index::servePage(HttpResponse& response) {
    constexpr auto read_size = std::size_t(4096);
    auto stream = std::ifstream("/home/smushed/Coding/http-server/assets/index.html");
    stream.exceptions(std::ios_base::badbit);

    if (not stream) {
        throw std::ios_base::failure("file does not exist");
    }

    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(& buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    response.updateWithResult(200, "Success", out);
    // const std::ifstream indexHtml ("/home/smushed/Coding/http-server/assets", std::ios::in | std::ios::binary);
    // if (!indexHtml.is_open()) {
    //     std::cout << "Error opening index.html" << std::endl;
    //     throw std::runtime_error("Error opening index.html");
    // }
    // std::stringstream ss;
    // ss << indexHtml.rdbuf();
    // std::cout << ss.str() << std::endl;
    // response.updateWithResult(200, "Success", ss.str());
    // return ss.str();

}
