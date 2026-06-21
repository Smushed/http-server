#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#include "Listener.h"


int main(int argc, char *argv[]) {
    Listener listener {};
    listener.listenOnPort(argv);

    return 0;
}
