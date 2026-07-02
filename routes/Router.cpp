#include "Router.h"

void Router::registerRoute(const Route& route) {
    this->m_routeList[route.getMethod()].push_back(route);
}

std::vector<Route> Router::getRoutesByMethod(HttpMethod reqMethod) {
    for (const auto& routesByMethod : this->m_routeList) {
        if (reqMethod == routesByMethod.first) {
            return routesByMethod.second;
        }
    }
}