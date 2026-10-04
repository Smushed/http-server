#include "Index.h"
#include <sstream>
#include "../../HttpMethods/HttpResponse.h"
#include "../../tools/LoadFile.h"

void Index::servePage(HttpResponse& response, const std::string_view subPage) {
    std::string file {};
    if (subPage.empty()) {
        file = loadFile("/home/smushed/Coding/http-server/assets/index/index.html");
        response.updateWithResult(200, "Success", file, "html");
    } else if (subPage == "app.js") {
        serveJS(response);
    } else if (subPage == "styles.css") {
        serveCSS(response);
    } else {
        file = HttpResponse::serve404();
    }
}

void Index::serveJS(HttpResponse& response) {
    const std::string out = loadFile("/home/smushed/Coding/http-server/assets/index/app.js");
    response.updateWithResult(200, "Success", out, "js");
}

void Index::serveCSS(HttpResponse& response) {
    const std::string out = loadFile("/home/smushed/Coding/http-server/assets/index/styles.css");
    response.updateWithResult(200, "Success", out, "css");
}