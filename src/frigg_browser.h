#ifndef FRIGG_FRIGG_H
#define FRIGG_FRIGG_H

#include "frigg_web_page.h"
#include "client_handler.h"
#include <include/cef_base.h>
#include <condition_variable>
#include <thread>
#include <mutex>

//class guarded_thread : std::thread {
//public:
//    using std::thread::thread;
//    ~guarded_thread() {if (this->joinable()) this->join();}
//};

class FriggBrowser {
    friend class ClientApp;
public:
    FriggBrowser(int argc, char *argv[]);
    ~FriggBrowser();

    FriggWebPage openUrl(const char *url);

private:
    void run(int argc, char **argv);

    std::thread _thrd;
    std::mutex _mtx;
    std::condition_variable _cv;
    bool browser_init = false;

    CefWindowInfo window_info;
    CefBrowserSettings browser_settings;
    CefRefPtr<ClientHandler> client_handler;

};

#endif //FRIGG_FRIGG_H
