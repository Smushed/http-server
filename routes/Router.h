#ifndef HTTP_SERVER_ROUTES_H
#define HTTP_SERVER_ROUTES_H
#include <vector>
#include <map>
#include "Route.h"
#include "../HttpMethod.h"


class Router {
    public:
        void registerRoute(const Route& route);
        std::vector<Route> getRoutesByMethod(HttpMethod reqMethod);
    private:
        std::map<HttpMethod,std::vector<Route>> m_routeList;
};


#endif //HTTP_SERVER_ROUTES_H
