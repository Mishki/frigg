#include <iostream>
#include "frigga.h"

int main(int argc, char *argv[]) {
    std::cout << "hello world!!!" << std::endl;
    Frigga frigga;
    frigga.init(argc, argv);

    return 0;
}