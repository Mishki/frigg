#ifndef FRIGG_FRIGG_H
#define FRIGG_FRIGG_H

#include <uuid/uuid.h>
#include <thread>
#include <mqueue.h>
#include <unistd.h>
#include <libltdl/lt_system.h>
#include <random>
#include <future>
#include <stdlib.h>
#include "client_app.h"
#include "request.h"
#include "session.h"

#include <X11/Xlib.h>

class Browser {
    friend class ClientApp;
    friend class Session;

public:
    Browser() {};
    Browser(int argc, char *argv[]);
    ~Browser();

    Session tab(std::string url);


private:
    void mqComm();

    pid_t cef_pid;
    std::thread thrd;
    mqd_t srv_mq, cli_mq;
    std::string srv_name, cli_name;
    std::map<std::string, std::promise<long>> promises;

};

#endif //FRIGG_FRIGG_H
