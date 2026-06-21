//
// Created by smushed on 6/20/26.
//
#include <iostream>
#include <netdb.h>
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

    int BUF_SIZE {500};
    char buf[BUF_SIZE];
    socklen_t peer_addrlen;
    addrinfo hints{};
    addrinfo *result, *rp;
    sockaddr_storage peer_addr {};

    int sfd, s;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    hints.ai_canonname = nullptr;
    hints.ai_addr = nullptr;
    hints.ai_next = nullptr;

    s = getaddrinfo(nullptr, argv[1], &hints, &result);
    if (s != 0) {
        fprintf(stderr, "%s\n", gai_strerror(s));
    }

    for (rp = result; rp != nullptr; rp = rp->ai_next) {
        sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (sfd == -1) continue;
        if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) break;
        close(sfd);
    }
    freeaddrinfo(result);
    if (rp == nullptr) {
        fprintf(stderr, "can't bind");
    }

    while (true) {
        char host[NI_MAXHOST], service[NI_MAXSERV];

        auto *peer_ptr = (sockaddr *) &peer_addr;
        peer_addrlen = sizeof(peer_addr);
        ssize_t nread = recvfrom(sfd, buf, BUF_SIZE, 0, peer_ptr, &peer_addrlen);
        if (nread == -1) continue;

        s = getnameinfo(peer_ptr, peer_addrlen, host, NI_MAXHOST, service,
            NI_MAXSERV, NI_NUMERICSERV);

        if (s == 0) {
            printf("received %zd bytes from: %s %s\n", nread, host, service);
        } else {
            fprintf(stderr, "error: %s", gai_strerror(s));
        }

        if (sendto(sfd, buf, nread, 0, peer_ptr,
           peer_addrlen) != nread)
        {
            fprintf(stderr, "Error sending response\n");
        }
    }
}

// class Listener {
//     public:
//         int listenOnPort() {
//             int sock = socket(AF_INET6, SOCK_STREAM, 0);
//             if (sock < 0) {
//                 perror("Failed creating socket");
//                 exit(EXIT_FAILURE);
//             }
//             bind(sock, struct )
//
//         }
// };