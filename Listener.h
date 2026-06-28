#ifndef HTTP_SERVER_LISTENER_H
#define HTTP_SERVER_LISTENER_H
// #include "route/HttpRoute.h"


class Listener {
    public:
        void run();
        Listener(char *argv[]);
        ~Listener();
    private:
        void spinUp();
        void respond(int, std::string_view);
        int listeningSocket{-1};
        const int BUF_SIZE{8192};
};


#endif //HTTP_SERVER_LISTENER_H
