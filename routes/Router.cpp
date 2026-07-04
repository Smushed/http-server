#include "Router.h"
#include <iostream>
#include <sys/socket.h>
#include "StatusCodes.h"
#include "../HttpMethods/HttpResponse.h"

constexpr std::string spacer() {return "\r\n";}

void Router::registerRoute(const Route& route) {
    this->m_routeList[route.getMethod()].push_back(route);
}

void Router::processRequest(const int& socket, HttpRequest request) {
    const std::vector<Route>& routes = this->getRoutesByMethod(request.getMethod());
    const Route* reqRoute = nullptr;
    for (const auto& route : routes) {
        if (request.getURI() == route.getUri()) {
            reqRoute = &route;
            break;
        }
    }

    HttpResponse response {};
    try {
        if (!reqRoute) {
            const std::string& fourOFourMessage{STATUS_CODES.at(404)};
            response.buildResponse(1, 404, fourOFourMessage, fourOFourMessage);
            // response = buildResponse(request.getVersion(), fourOFourMessage);
        } else {
            // response = reqRoute->performAction();
        }
    } catch (error_t err) {
        std::cout << "Error processing request\n" << err << std::endl;
        const std::string& serverErrorMessage{STATUS_CODES.at(500)};
        response.buildResponse(1, 500, serverErrorMessage, serverErrorMessage);

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

std::string Router::buildResponse(const std::string& version, const std::string_view message) {
    const unsigned long responseLen = message.size();

    std::string response = version + " " + message + spacer() + "Content-Type: text/plain" +
        spacer() + "Content-Length: " + std::to_string(responseLen) + spacer() + spacer() + message;

    return response;
}
