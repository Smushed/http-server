#include "HttpPageRoute.h"
#include <fstream>
#include "../tools/LoadFile.h"

HttpPageRoute::HttpPageRoute(std::string uri, const std::string& filePath, HttpResponse& response)
        : Route(HttpMethod::GET, std::move(uri)) {
    m_filePath = filePath;
    const std::string out = loadFile(filePath);
    response.updateWithResult(200, "Success", out, "html");
}
