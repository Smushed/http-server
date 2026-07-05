#ifndef HTTP_SERVER_ROUTE_H
#define HTTP_SERVER_ROUTE_H
#include <functional>
#include <string>
#include "../HttpMethod.h"

class Route {
    public:
        [[nodiscard]] HttpMethod getMethod() const { return m_method; }
        [[nodiscard]] std::string getUri() const { return m_uri; }
        // Route()= default;
        Route(HttpMethod method, std::string incomingUri, const std::function<std::string()>& action);
        Route(HttpMethod method, std::string incomingUri);
        void performAction() const;
    private:
        std::function<std::string()> m_action;
        std::string m_uri;
        HttpMethod m_method;
};


#endif //HTTP_SERVER_ROUTE_H
