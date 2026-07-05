#include "Index.h"

std::string Index::servePage() {
    const std::ifstream indexHtml ("../../assets/index.html", std::ios::in | std::ios::binary);
    if (!indexHtml.is_open()) {
        std::cout << "Error opening index.html" << std::endl;
        throw std::runtime_error("Error opening index.html");
    }
    std::stringstream ss;
    ss << indexHtml.rdbuf();
    return ss.str();
}
