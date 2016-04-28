#include <iostream>
#include "frigg_browser.h"
#include "frigg_web_page.h"

int main(int argc, char *argv[]) {
    printf("Sample program started.\n");

    FriggBrowser browser(argc, argv);

    browser.openUrl("https://www.google.com/");
    browser.openUrl("http://www.omgubuntu.co.uk/");

//    FriggWebPage wp = browser.openUrl("https://www.google.com/");
//    FriggWebPage wp = browser.openUrl("http://www.omgubuntu.co.uk/");


    return 0;
}
