#ifndef FRIGGA_FRIGGA_H
#define FRIGGA_FRIGGA_H

#include <thread>

class guarded_thread : std::thread {
public:
    using std::thread::thread;
    ~guarded_thread() {if (this->joinable()) this->join();}
};

class Frigga {
public:
    Frigga(int argc, char *argv[]);
    ~Frigga();
private:
};

#endif //FRIGGA_FRIGGA_H
