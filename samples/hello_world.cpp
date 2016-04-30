#include "frigg.h"
#include "chrono"

int main(int argc, char *argv[]) {
    printf("Sample program started.\n");

    Browser browser1(argc, argv);
    Session session1 = browser1.tab("http://www.stroustrup.com/");
    printf("WWW: https://www.google.com/\n");
    printf("BROWSER ID: %d\n", session1.getBid());
//    printf("%s\n", session1.html().c_str());

    for (int i = 0; i < 2; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        session1.js(
            "var img = window.document.querySelector(\"body > center:nth-child(4) > img\"); img.src = \"https://i.ytimg.com/vi/dcC26nnipxs/maxresdefault.jpg\"; img.height = 437; img.width = 700;"
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        session1.js(
            "var img = window.document.querySelector(\"body > center:nth-child(4) > img\"); img.src = \"https://www.chu.cam.ac.uk/media/assets/4b/34e37fd955c65860a33f42989d1399ce3a0c5c.jpg\"; img.height = 437; img.width = 750;"
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        session1.js(
            "var img = window.document.querySelector(\"body > center:nth-child(4) > img\"); img.src = \"http://www.wired.com/images_blogs/thisdayintech/2010/10/coding_professor.jpg\"; img.height = 437; img.width = 670;"
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        session1.js(
            "var img = window.document.querySelector(\"body > center:nth-child(4) > img\"); img.src = \"http://farm2.static.flickr.com/1286/968223285_d3ed21b818.jpg\"; img.height = 437; img.width = 670;"
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        session1.js(
            "var img = window.document.querySelector(\"body > center:nth-child(4) > img\"); img.src = \"https://i.ytimg.com/vi/CsPOA57kBsM/maxresdefault.jpg\"; img.height = 437; img.width = 670;"
        );

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        session1.js(
            "var img = window.document.querySelector(\"body > center:nth-child(4) > img\"); img.src = \"http://www.computerworld.dk/fil/26029/540?scale_up\"; img.height = 450; img.width = 670;"
        );
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//    FriggSession session2 = browser.openUrl("http://www.stroustrup.com/");
//    printf("NUMBER IS: %d\n", session2.id());
//    printf("%s\n", session2.html());

}