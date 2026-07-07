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
    for (const auto& route : routes) {
        if (request.getURI() == route.getUri()) {
            reqRoute = &route;
            break;
        }
    }

    HttpResponse response(request.getVersion());
    try {
        if (!reqRoute) {
            const std::string& fourOFourMessage{STATUS_CODES.at(404)};
            response.updateWithResult(404, fourOFourMessage, fourOFourMessage);
        } else {
            reqRoute->performAction(response);
        }
    } catch (error_t err) {
        std::cout << "Error processing request\n" << err << std::endl;
        const std::string& serverErrorMessage{STATUS_CODES.at(500)};
        response.build(request.getVersion(), 500, serverErrorMessage, serverErrorMessage);
    }
    response.sendResponse(socket, 0);
    // send(socket, response.data(), response.size(), 0);
}

const std::vector<Route>& Router::getRoutesByMethod(HttpMethod reqMethod) {
    auto iter = this->m_routeList.find(reqMethod);

    if (iter != this->m_routeList.end()) {
        return iter->second;
    }
    static std::vector<Route> emptyResult {};
    return emptyResult;
}
