#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>

#include "Listener.h"


int main(int argc, char *argv[]) {
    if (argv[1] == 0) {
        std::cout << "Please provide a port number";
        return 0;
    }
    Listener server(argv);
    server.run();

    return 0;
}
