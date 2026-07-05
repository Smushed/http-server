#ifndef HTTP_SERVER_ROUTES_H
#define HTTP_SERVER_ROUTES_H
#include <vector>
#include <map>
#include "Route.h"
#include "../HttpMethod.h"
#include "../HttpMethods/HttpRequest.h"

class Router {
    public:
        void registerRoute(const Route& route);
        void processRequest(const int& socket, HttpRequest request);
    private:
        const std::vector<Route>& getRoutesByMethod(HttpMethod reqMethod);
        std::map<HttpMethod,std::vector<Route>> m_routeList;
};


#endif //HTTP_SERVER_ROUTES_H
