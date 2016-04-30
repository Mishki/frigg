#ifndef FRIGG_FRIGG_H
#define FRIGG_FRIGG_H

#include <uuid/uuid.h>
#include <thread>
#include <mqueue.h>
#include <unistd.h>
#include <libltdl/lt_system.h>
#include <random>
#include <stdlib.h>
#include <ctime>
#include "client_app.h"
#include "session.h"

#include <X11/Xlib.h>

#define MSG_SIZE 8192

#define QUIT        1
#define SESSION     2

typedef struct request {
    int method;
    long shmem;
//    char args[0];
} request;

class Browser {
    friend class ClientApp;

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

};

#endif //FRIGG_FRIGG_H
