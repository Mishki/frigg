#include <iostream>
#include <chrono>
#include "frigg.h"

int main(int argc, char *argv[]) {
    printf("Sample program started.\n");

    FriggBrowser browser(argc, argv);

    browser.openUrl("https://www.google.com/");
    browser.openUrl("http://www.omgubuntu.co.uk/");

    //    WebPage wp = foreman.open("https://www.google.com");


    return 0;
}
