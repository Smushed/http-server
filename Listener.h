//
// Created by smushed on 6/20/26.
//

#ifndef HTTP_SERVER_LISTENER_H
#define HTTP_SERVER_LISTENER_H


class Listener {
    public:
        static int listenOnPort(char *argv[]);
    private:
        [[noreturn]] static int spinUp(char *argv[]);
};


#endif //HTTP_SERVER_LISTENER_H
