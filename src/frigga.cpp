#include "client_app.h"

//browser process entry point
int main(int argc, char *argv[]) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr <ClientApp> app(new ClientApp); //unique ref ptr created by cef, CLientApp is our class that we have over-written
    //Creating app that is a shared ptr of ClientApp. It handles process level callbacks

    int exit_code = CefExecuteProcess(main_args, app.get(), NULL);
    if (exit_code >= 0) {
        return exit_code;
    } //chrome has multiple threads (eg rendering, js processing)- this is for that

    CefSettings settings;
    //Initializing cef
    CefInitialize(main_args, settings, app.get(), NULL); //spawns browser threads and properties
    //shared space for communication between threads

    //Running cef message loop
    CefRunMessageLoop(); //Blocking loop goes thru msg queue and figures out who the message is for, and the thread will execute whatever
    CefShutdown(); //termination msg to all threads to stop
    return 0;
}
