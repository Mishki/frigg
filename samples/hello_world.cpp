#include <iostream>
#include "frigga.h"

int main(int argc, char *argv[]) {
    printf("hello world\n");

    Frigga foreman(argc, argv);

    foreman.open_url("https://www.google.com/");
    foreman.open_url("http://www.omgubuntu.co.uk/");

    //    WebPage wp = foreman.open("https://www.google.com");


    return 0;
}
