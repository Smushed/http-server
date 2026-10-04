#include "Router.h"
#include <iostream>
#include "StatusCodes.h"
#include "../HttpMethods/HttpResponse.h"


void Router::registerRoute(const Route& route) {
    this->m_routeList[route.getMethod()].push_back(route);
}

void Router::processRequest(const int& socket, HttpRequest request) {
    const std::vector<Route>& routes = this->getRoutesByMethod(request.getMethod());
    const Route* reqRoute = nullptr;
    const std::string& uri = request.getURI();
    std::string baseRoute = uri;
    std::string subPath;

    size_t secondSlashPos = uri.find('/', 1);

    if (secondSlashPos != std::string::npos) {
        baseRoute = uri.substr(0, secondSlashPos);
        subPath = uri.substr(secondSlashPos + 1);
    }

    for (const auto& route : routes) {
        if (baseRoute == route.getUri()) {
            reqRoute = &route;
            break;
        }
    }

    HttpResponse response(request.getVersion());
    try {
        if (!reqRoute) {
            const std::string out = loadFile("/home/smushed/Coding/http-server/assets/404/404.html");
            response.updateWithResult(200, "Success", out, "html");
        } else {
            reqRoute->performAction(response, subPath);
        }
    } catch (error_t err) {
        std::cout << "Error processing request\n" << err << std::endl;
        const std::string& serverErrorMessage{STATUS_CODES.at(500)};
        response.build(request.getVersion(), 500, serverErrorMessage, serverErrorMessage);
    }
    response.sendResponse(socket, 0);
}

const std::vector<Route>& Router::getRoutesByMethod(HttpMethod reqMethod) {
    auto iter = this->m_routeList.find(reqMethod);

    if (iter != this->m_routeList.end()) {
        return iter->second;
    }
    static std::vector<Route> emptyResult {};
    return emptyResult;
}