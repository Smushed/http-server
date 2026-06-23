#include <iostream>
#include <netdb.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include "Listener.h"
#include <cstring>
#include <unistd.h>

int Listener::listenOnPort(char *argv[]) {
    spinUp(argv);
}

[[noreturn]] int Listener::spinUp(char *argv[]) {
    int sock = socket(AF_INET6, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Failed creating socket");
        exit(EXIT_FAILURE);
    }

    int BUF_SIZE {4};
    char buf[BUF_SIZE];
    socklen_t peer_addrlen;
    addrinfo hints{};
    addrinfo *result, *rp;
    sockaddr_storage peer_addr {};

    int listeningSocket{}, s{};
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
        if (bind(listeningSocket, rp->ai_addr, rp->ai_addrlen) == 0) break;
        close(listeningSocket);
    }
    freeaddrinfo(result);
    if (rp == nullptr) {
        fprintf(stderr, "can't bind");
    }
    listen(listeningSocket, 5);
    socklen_t addr_size = sizeof peer_addr;

    while (true) {
        int connectionSocket = accept(listeningSocket, (struct sockaddr *)&peer_addr , &addr_size);
        switch (connectionSocket) {
            case 0: printf("Connection Terminated\n"); break;
            case -1: printf("error\n"); break;
            default: fprintf(stdout, "Socket # %i\n", connectionSocket);
        }

        std::string requestAccumulator {};

        while (true) {
            ssize_t bytesReceived = recv(connectionSocket, buf, BUF_SIZE, 0);
            switch (bytesReceived) {
                case 0: printf("Connection Terminated\n"); break;
                case -1: perror("recv failed"); break;
                default: fprintf(stdout, "%ld: bytes received\n", bytesReceived);
            }

            if (bytesReceived > 0) {
                requestAccumulator.append(buf, bytesReceived);
            } else if (bytesReceived == 0) {
                close(connectionSocket);
                break;
            } else {
                break;
            }
        }
        std::cout << requestAccumulator;
        close(connectionSocket);
    }

    std::string response = "This is actually working";


    // while (true) {
    //     char host[NI_MAXHOST], service[NI_MAXSERV];
    //
    //     auto *peer_ptr = (sockaddr *) &peer_addr;
    //     peer_addrlen = sizeof(peer_addr);
    //     ssize_t nread = recvfrom(sfd, buf, BUF_SIZE, 0, peer_ptr, &peer_addrlen);
    //     if (nread == -1) continue;
    //
    //     s = getnameinfo(peer_ptr, peer_addrlen, host, NI_MAXHOST, service,
    //         NI_MAXSERV, NI_NUMERICSERV);
    //
    //     if (s == 0) {
    //         printf("received %zd bytes from: %s %s\n", nread, host, service);
    //     } else {
    //         fprintf(stderr, "error: %s", gai_strerror(s));
    //     }
    //
    //     if (sendto(sfd, buf, nread, 0, peer_ptr,
    //        peer_addrlen) != nread)
    //     {
    //         fprintf(stderr, "Error sending response\n");
    //     }
    // }
}

std::string Listener::readBytes(int socket, unsigned int x, void* buffer) {
    int bytesRead {0};
    return "";
}
