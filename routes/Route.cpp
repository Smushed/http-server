#include "Route.h"
#include <functional>
#include <iostream>
#include <string>
#include <utility>

#include "../HttpMethods/HttpResponse.h"

Route::Route(const HttpMethod method,
             std::string incomingUri,
             const std::function<std::string(HttpResponse&)>& action) {
    this->m_method = method;
    this->m_uri = std::move(incomingUri);
    this->m_action = action;
}

std::string testing(HttpResponse response) {
    std::cout << "up";
    return "up";
}

Route::Route(const HttpMethod method, std::string incomingUri)
    :   m_action(&testing),
        m_uri(std::move(incomingUri)),
        m_method(method)
{}

void Route::performAction(HttpResponse& response) const {
    if (this->m_action) {
        std::string result = this->m_action(response);
        // response
    }
}
