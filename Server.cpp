#include <iostream>
#include <netdb.h>
#include <sys/socket.h>
#include "Server.h"
#include <cstring>
#include <sstream>
#include <unistd.h>
#include "HttpMethods/HttpRequest.h"
#include "routes/Router.h"
#include "routes/StatusCodes.h"
#include "routes/gets/Index.h"
#include "tools/ConnectionSocket.h"

Server::Server(char *argv[]) {
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
        listeningSocket = ConnectionSocket(socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol));
        if (listeningSocket.get() == -1) continue;

        int opt = 1;
        if (setsockopt(listeningSocket.get(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
            close(listeningSocket.get());
            freeaddrinfo(result);
            throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
        }

        if (bind(listeningSocket.get(), rp->ai_addr, rp->ai_addrlen) == 0) break;
        close(listeningSocket.get());
    }
    freeaddrinfo(result);
    if (rp == nullptr) {
        fprintf(stderr, "can't bind");
        throw std::runtime_error("Port is busy");
    }
}

Server::~Server() {
    if (listeningSocket.get() == -1) return;
}

void Server::run() {
    createRouter();
    spinUp();
}

void Server::createRouter() {
    router.registerRoute(Route {HttpMethod::GET, "/home", Index::servePage});
}

void Server::spinUp() {
    char buf[BUF_SIZE];
    sockaddr_storage peer_addr {};
    listen(listeningSocket.get(), 5);
    socklen_t addr_size = sizeof peer_addr;

    while (true) {
        const auto connectionSocket = ConnectionSocket(accept(listeningSocket.get(), (struct sockaddr *)&peer_addr , &addr_size));
        switch (connectionSocket.get()) {
            case 0: printf("Connection Terminated\n"); continue;
            case -1: {
                printf("error\n");
                continue;
            }
            default: ;
        }

        std::string requestAccumulator {};

        while (true) {
            const ssize_t bytesReceived = recv(connectionSocket.get(), buf, BUF_SIZE, 0);
            switch (bytesReceived) {
                case 0: printf("Connection Terminated\n"); break;
                case -1: perror("recv failed"); break;
                default: ;
            }

            bool receivedHeaders = false;

            if (bytesReceived > 0) {
                requestAccumulator.append(buf, bytesReceived);
                if (requestAccumulator.find("\r\n\r\n") != std::string::npos) {
                    receivedHeaders = true;
                    break;
                }
            } else {
                break;
            }
            if (!receivedHeaders) break;
        }

        try {
            const HttpRequest request {requestAccumulator};
            this->router.processRequest(connectionSocket, request);
        } catch (std::invalid_argument& err) {
            HttpResponse response{"1.1", 400, err.what(), ""};
            response.sendResponse(connectionSocket, 0);
        } catch (std::runtime_error& err) {
            std::string errorMessage {};
            if (!strcmp(err.what(), "")) {
                errorMessage = err.what();
            }
            HttpResponse response{"1.1", 500, errorMessage, ""};
            response.sendResponse(connectionSocket, 0);
        }
    }
}