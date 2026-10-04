#include "Route.h"
#include <functional>
#include <iostream>
#include <string>
#include <utility>

#include "../HttpMethods/HttpResponse.h"

Route::Route(const HttpMethod method,
             std::string incomingUri,
             const std::function<void(HttpResponse&, std::string_view)>& action) {
    this->m_method = method;
    this->m_uri = std::move(incomingUri);
    this->m_action = action;
}

Route::Route(const HttpMethod method, std::string incomingUri)
    :   m_uri(std::move(incomingUri)),
        m_method(method)
{}

void Route::performAction(HttpResponse& response, std::string_view subPath) const {
    if (this->m_action) {
        m_action(response, subPath);
    }
}
