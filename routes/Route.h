#ifndef HTTP_SERVER_ROUTE_H
#define HTTP_SERVER_ROUTE_H
#include <string>


class Route {
    public:
        std::string uri;
        Route(std::string incomingUri) : uri(std::move(incomingUri)) {}
        void performAction();
};


#endif //HTTP_SERVER_ROUTE_H
