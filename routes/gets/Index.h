#ifndef HTTP_SERVER_INDEX_H
#define HTTP_SERVER_INDEX_H
#include "../../HttpMethods/HttpResponse.h"

struct Index {
    static void servePage(HttpResponse& response);
    static void serveJS(HttpResponse& response);
    static void serveCSS(HttpResponse& response);
};


#endif //HTTP_SERVER_INDEX_H
