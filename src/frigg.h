#ifndef FRIGG_FRIGG_H
#define FRIGG_FRIGG_H

#include <cstdlib>
#include <thread>
#include <random>
#include <future>
#include <uuid>

//#include <unistd.h>

//#include <libltdl/lt_system.h>

#include "client_app.h"
#include "request.h"
#include "session.h"

#include <X11/Xlib.h>

class Browser {
    friend class ClientApp;
    friend class Session;

public:
    Browser();
    ~Browser();

//    Session tab(std::string url);

private:
    void ipc_loop();

    pid_t cef_pid;
    std::thread thrd;
    int srv_fd, cli_fd;
    std::string name;


    std::map<std::string, std::promise<long>> promises;
};

#endif //FRIGG_FRIGG_H
