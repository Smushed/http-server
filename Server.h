#ifndef HTTP_SERVER_LISTENER_H
#define HTTP_SERVER_LISTENER_H
#include "request/HttpRequest.h"
#include "routes/Router.h"

class Server {
    public:
        void run();
        Server(char *argv[]);
        ~Server();
    private:
        void spinUp();
        void createRouter();
        void respond(int, HttpRequest);
        Router router{};
        int listeningSocket{-1};
        const int BUF_SIZE{8192};
};


#endif //HTTP_SERVER_LISTENER_H
