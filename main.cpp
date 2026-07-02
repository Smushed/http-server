#include <iostream>
#include "Server.h"

int main(int argc, char *argv[]) {
    if (argv[1] == 0) {
        std::cout << "Please provide a port number";
        return 0;
    }
    Server server(argv);
    server.run();

    return 0;
}
