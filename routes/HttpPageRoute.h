#ifndef HTTP_SERVER_HTTPPAGEROUTE_H
#define HTTP_SERVER_HTTPPAGEROUTE_H
#include "Route.h"
#include <string>

class HttpPageRoute : Route {
    HttpPageRoute(std::string uri, const std::string& filePath, HttpResponse& response);

    private:
        std::string m_filePath {};
};


#endif //HTTP_SERVER_HTTPPAGEROUTE_H
