#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#include "Listener.h"


int main(int argc, char *argv[]) {
    Listener::listenOnPort(argv);

    return 0;
}
