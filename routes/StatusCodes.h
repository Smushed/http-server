#ifndef HTTP_SERVER_STATUSCODES_H
#define HTTP_SERVER_STATUSCODES_H

#include <map>

inline const std::map<int, const char*> STATUS_CODES = {
    {200, "OK"},
    {404, "404 Not Found"},
    {500, "Internal Server Error"}
};

#endif //HTTP_SERVER_STATUSCODES_H
