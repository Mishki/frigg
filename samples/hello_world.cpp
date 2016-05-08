#include "frigg.h"
#include "chrono"

int main(int argc, char *argv[]) {
    printf("Sample program started.\n");

    Browser browser1(argc, argv);
    Session session1 = browser1.tab("http://www.stroustrup.com/");
    printf("WWW: https://www.google.com/\n");
    printf("BROWSER ID: %d\n", session1.getBid());

    session1.js("var img = window.document.querySelector(\"body > center:nth-child(4) > img\"); img.src = \"https://i.ytimg.com/vi/dcC26nnipxs/maxresdefault.jpg\"; img.height = 437; img.width = 700;");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}