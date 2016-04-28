#ifndef FRIGG_FRIGG_H
#define FRIGG_FRIGG_H

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
public:
    FriggBrowser(int argc, char *argv[]);
    ~FriggBrowser();

    void initializer();
    void openUrl(const char *url);

private:
    void run(int argc, char **argv);

    std::thread _thrd;
    std::mutex _mtx;
    std::condition_variable _cv;
    bool initialized = false;
};

#endif //FRIGG_FRIGG_H
