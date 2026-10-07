#ifndef HTTP_SERVER_CONNECTIONSOCKET_H
#define HTTP_SERVER_CONNECTIONSOCKET_H
#include <unistd.h>

class ConnectionSocket {
    public:
        explicit ConnectionSocket(int fd) : m_fd{fd} {}

        ~ConnectionSocket() {
            if (m_fd >= 0) {
                close(m_fd);
            }
        }
        ConnectionSocket(const ConnectionSocket&) = delete;
        ConnectionSocket& operator=(const ConnectionSocket&) = delete;
        [[nodiscard]] int get() const { return m_fd; }
    private:
        int m_fd;
};

#endif //HTTP_SERVER_CONNECTIONSOCKET_H
