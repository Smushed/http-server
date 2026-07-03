#include "Router.h"
#include <iostream>
#include <sys/socket.h>
#include "StatusCodes.h"

void Router::registerRoute(const Route& route) {
    this->m_routeList[route.getMethod()].push_back(route);
}

void Router::processRequest(int socket, HttpRequest request) {
    const std::vector<Route>& routes = this->getRoutesByMethod(request.getMethod());
    const Route* reqRoute = nullptr;
    for (const auto& route : routes) {
        if (request.getURI() == route.getUri()) {
            reqRoute = &route;
            break;
        }
    }
    std::string response{};
    if (!reqRoute) {
        const std::string& statusCodeMessage{STATUS_CODES.at(404)};
        response = buildResponse(request.getVersion(), statusCodeMessage);
    }
    send(socket, response.data(), response.size(), 0);
}

const std::vector<Route>& Router::getRoutesByMethod(HttpMethod reqMethod) {
    auto iter = this->m_routeList.find(reqMethod);

    if (iter != this->m_routeList.end()) {
        return iter->second;
    }
    static std::vector<Route> emptyResult {};
    return emptyResult;
}

std::string Router::buildResponse(std::string& version, const std::string& message) {
    int responseLen = message.size();
    const std::string spacer = "\r\n";

    std::string response = version + " " + message + spacer + "Content-Type: text/plain" +
        spacer + "Content-Length: " + std::to_string(responseLen) + spacer + spacer + message;

    return response;
}
