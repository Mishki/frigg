#ifndef FRIGG_WEB_PAGE_H
#define FRIGG_WEB_PAGE_H

#include <uuid/uuid.h>
#include <stdlib.h>
#include <string>
#include <future>
#include <map>
#include <mqueue.h>
#include "request.h"

class Session {
public:
    Session() {};
    Session(std::map<std::string, std::promise<long>> *promises, mqd_t srv_mq, int bid);
    ~Session();

    int getBid();
    std::string html();
    void js(std::string code);

private:
    int bid;
    std::map<std::string, std::promise<long>> *promises;
    mqd_t srv_mq;
};

#endif // FRIGG_WEB_PAGE_H
