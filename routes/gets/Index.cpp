#include "Index.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "../../HttpMethods/HttpResponse.h"

constexpr auto read_size = std::size_t(4096);

constexpr std::string loadFile(const std::string& filePath) {
    auto stream = std::ifstream(filePath);
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
    stream.close();
    return out;
}

void Index::servePage(HttpResponse& response) {
    const std::string out = loadFile("/home/smushed/Coding/http-server/assets/index/index.html");
    response.updateWithResult(200, "Success", out, "html");
}

void Index::serveJS(HttpResponse& response) {
    const std::string out = loadFile("/home/smushed/Coding/http-server/assets/index/app.js");
    response.updateWithResult(200, "Success", out, "js");
}

void Index::serveCSS(HttpResponse& response) {
    const std::string out = loadFile("/home/smushed/Coding/http-server/assets/index/styles.css");
    response.updateWithResult(200, "Success", out, "css");
}