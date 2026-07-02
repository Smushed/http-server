#ifndef HTTP_SERVER_ROUTE_H
#define HTTP_SERVER_ROUTE_H
#include <functional>
#include <string>
#include "../HttpMethod.h"

class Route {
    public:
        HttpMethod getMethod() const { return m_method; }
        std::string getUri() const { return m_uri; }
        Route(HttpMethod method,
            std::string incomingUri,
            std::function<int()> action);
        Route(HttpMethod method,
            std::string incomingUri);
        void performAction() const;
    private:
        std::function<int()> m_action;
        std::string m_uri;
        HttpMethod m_method;
};


#endif //HTTP_SERVER_ROUTE_H
