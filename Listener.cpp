#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include "Listener.h"
#include <cstring>
#include <sstream>
#include <unistd.h>
#include "request/HttpRequest.h"
#include "routes/Router.h"

Listener::Listener(char *argv[]) {
    addrinfo hints{};
    addrinfo *result, *rp;

    int s{};
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    hints.ai_canonname = nullptr;
    hints.ai_addr = nullptr;
    hints.ai_next = nullptr;

    s = getaddrinfo(nullptr, argv[1], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "%s\n", gai_strerror(s));
    }

    for (rp = result; rp != nullptr; rp = rp->ai_next) {
        listeningSocket = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (listeningSocket == -1) continue;

        int opt = 1;
        if (setsockopt(listeningSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
        }

        if (bind(listeningSocket, rp->ai_addr, rp->ai_addrlen) == 0) break;
        close(listeningSocket);
    }
    freeaddrinfo(result);
    if (rp == nullptr) {
        fprintf(stderr, "can't bind");
        throw std::runtime_error("Port is busy");
    }
}

Listener::~Listener() {
    if (listeningSocket == -1) return;
    close(listeningSocket);
}

void Listener::run() {
    // this->base = HttpRoute(HttpMethod::GET);
    createRouter();
    spinUp();
}

void Listener::createRouter() {
    Router router{};
    Route index{"/index.html"};

    router.registerRoute(index);
}

void Listener::respond(int socket, std::string_view sv) {
    ssize_t sendResponse = send(socket, sv.data(), sv.size(), 0);
    std::cout << "Send Reponse: " << sendResponse;
}

void Listener::spinUp() {
    char buf[BUF_SIZE];
    sockaddr_storage peer_addr {};
    listen(listeningSocket, 5);
    socklen_t addr_size = sizeof peer_addr;

    while (true) {
        const int connectionSocket = accept(listeningSocket, (struct sockaddr *)&peer_addr , &addr_size);
        switch (connectionSocket) {
            case 0: printf("Connection Terminated\n"); continue;
            case -1: printf("error\n");
;
            default: ;
        }

        std::string requestAccumulator {};

        while (true) {
            const ssize_t bytesReceived = recv(connectionSocket, buf, BUF_SIZE, 0);
            switch (bytesReceived) {
                case 0: printf("Connection Terminated\n"); break;
                case -1: perror("recv failed"); break;
                default: ;
            }


            if (bytesReceived > 0) {
                requestAccumulator.append(buf, bytesReceived);
                if (requestAccumulator.find("\r\n\r\n") != std::string::npos) {
                    break;
                }
            } else if (bytesReceived == 0) {
                close(connectionSocket);
                break;
            } else {
                break;
            }
        }

        try {
            HttpRequest request(requestAccumulator);
            this->respond(connectionSocket, requestAccumulator);
        } catch (std::runtime_error& err) {
            this->respond(connectionSocket, err.what());
        }

        close(connectionSocket);
    }
}