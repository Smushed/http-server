#ifndef HTTP_SERVER_ROUTES_H
#define HTTP_SERVER_ROUTES_H
#include <vector>
#include <map>
#include "Route.h"
#include "../HttpMethod.h"


class Router {
    std::map<HttpMethod,std::vector<Route>> routeList;
    public:
        void registerRoute(const Route& route);
        std::vector<Route> getRoutesByMethod();
};


#endif //HTTP_SERVER_ROUTES_H
