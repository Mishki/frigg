#include "frigg.h"
#include "chrono"

int main(int argc, char *argv[]) {
    printf("Sample program started.\n");

    Browser browser1(argc, argv);
    Session session1 = browser1.tab("https://www.google.com/");
    printf("WWW: https://www.google.com/\n");
    printf("BROWSER ID: %d\n", session1.getBid());
    printf("%s\n", session1.html().c_str());

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

//    FriggSession session2 = browser.openUrl("http://www.stroustrup.com/");
//    printf("NUMBER IS: %d\n", session2.id());
//    printf("%s\n", session2.html());

}
