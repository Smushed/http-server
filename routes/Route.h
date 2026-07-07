#ifndef HTTP_SERVER_ROUTE_H
#define HTTP_SERVER_ROUTE_H
#include <functional>
#include <string>
#include "../HttpMethod.h"
#include "../HttpMethods/HttpResponse.h"

class Route {
    public:
        [[nodiscard]] HttpMethod getMethod() const { return m_method; }
        [[nodiscard]] std::string getUri() const { return m_uri; }
        // Route()= default;
        Route(HttpMethod method, std::string incomingUri, const std::function<void(HttpResponse&)>& action);
        Route(HttpMethod method, std::string incomingUri);
        void performAction(HttpResponse& response) const;
    private:
        std::function<void(HttpResponse&)> m_action;
        std::string m_uri;
        HttpMethod m_method;
};


#endif //HTTP_SERVER_ROUTE_H
