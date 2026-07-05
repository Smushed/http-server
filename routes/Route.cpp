#include "Route.h"
#include <functional>
#include <iostream>
#include <string>
#include <utility>

Route::Route(const HttpMethod method,
        std::string incomingUri,
        const std::function<std::string()>& action) {
    this->m_method = method;
    this->m_uri = std::move(incomingUri);
    this->m_action = action;
}

std::string testing() {
    std::cout << "up";
    return "up";
}

Route::Route(const HttpMethod method, std::string incomingUri)
    :   m_action(&testing),
        m_uri(std::move(incomingUri)),
        m_method(method)
{}

void Route::performAction() const {
    if (this->m_action) {
        this->m_action();
    }
}
