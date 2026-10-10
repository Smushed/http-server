#ifndef HTTP_SERVER_SENDCLIENTERROR_H
#define HTTP_SERVER_SENDCLIENTERROR_H
#include "HttpResponse.h"

constexpr void SendClientError(const ConnectionSocket& connectionSocket) {
    HttpResponse response{"1.1", 400, "Bad Request", ""};
    response.sendResponse(connectionSocket, 0);
}

#endif //HTTP_SERVER_SENDCLIENTERROR_H
