#ifndef HTTP_SERVER_LOADFILE_H
#define HTTP_SERVER_LOADFILE_H
#include <fstream>
#include <string>

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


#endif //HTTP_SERVER_LOADFILE_H
