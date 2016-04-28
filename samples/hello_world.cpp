#include <iostream>
#include "frigg_browser.h"

int main(int argc, char *argv[]) {
    printf("Sample program started.\n");

    FriggBrowser browser(argc, argv);

    FriggWebPage wp1 = browser.openUrl("https://www.google.com/");
    printf("NUMBER IS: %d\n", wp1.getVal());

    FriggWebPage wp2 = browser.openUrl("http://www.stroustrup.com/");
    printf("NUMBER IS: %d\n", wp2.getVal());

}
