#include <iostream>
#include "frigga.h"

int main(int argc, char *argv[]) {
    std::cout << "hello world!!!" << std::endl;
    Frigga frigga{argc, argv};
    std::cout << "ended" << std::endl;

    return 0;
}
