#include <iostream>
#include <chrono>
#include "frigg_browser.h"
#include "frigg_web_page.h"

int main(int argc, char *argv[]) {
    printf("Sample program started.\n");
    {
        FriggBrowser browser(argc, argv);

        FriggWebPage wp1 = browser.openUrl("https://www.google.com/");
        printf("NUMBER IS: %d\n", wp1.getVal());

        FriggWebPage wp2 = browser.openUrl("http://www.stroustrup.com/");
        printf("NUMBER IS: %d\n", wp2.getVal());
    }

//    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//    {
//        FriggBrowser browser2(argc, argv);
//
//        FriggWebPage wp3 = browser2.openUrl("https://www.google.com/");
//        printf("NUMBER IS: %d\n", wp3.getVal());
//
//        FriggWebPage wp4 = browser2.openUrl("http://www.stroustrup.com/");
//        printf("NUMBER IS: %d\n", wp4.getVal());
//    }

    return 0;
}
