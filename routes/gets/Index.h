#ifndef HTTP_SERVER_INDEX_H
#define HTTP_SERVER_INDEX_H
#include <fstream>
#include "../../HttpMethods/HttpResponse.h"

struct Index {
    static std::string servePage(HttpResponse& response);
};


#endif //HTTP_SERVER_INDEX_H
