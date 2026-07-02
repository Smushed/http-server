#include "Route.h"
#include <functional>
#include <iostream>
#include <string>
#include <utility>

Route::Route(const HttpMethod method,
        std::string incomingUri,
        std::function<int()> action) {
    this->m_method = method;
    this->m_uri = std::move(incomingUri);
    this->m_action = std::move(action);
}

int testing() {
    std::cout << "up";
    return 1;
}

Route::Route(const HttpMethod method, std::string incomingUri) {
    this->m_method = method;
    this->m_uri = std::move(incomingUri);
    this->m_action = testing;
}

void Route::performAction() const {
    if (this->m_action) {
        this->m_action();
    }
}
