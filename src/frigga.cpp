#include "frigga.h"
#include "client_app.h"

#include <X11/Xlib.h>
#include <iostream>
#include "include/base/cef_logging.h"

// TODO REMOVE
namespace {

    int XErrorHandlerImpl(Display *display, XErrorEvent *event) {
        LOG(WARNING)
        << "X error received: "
        << "type " << event->type << ", "
        << "serial " << event->serial << ", "
        << "error_code " << static_cast<int>(event->error_code) << ", "
        << "request_code " << static_cast<int>(event->request_code) << ", "
        << "minor_code " << static_cast<int>(event->minor_code);
        return 0;
    }

    int XIOErrorHandlerImpl(Display *display) {
        return 0;
    }

}

//guarded_thread th;

Frigga::Frigga() {}
Frigga::~Frigga() {}

int Frigga::init(int argc, char *argv[]) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr<ClientApp> app(new ClientApp);

    //    int exit_code = CefExecuteProcess(main_args, app.get(), NULL);
    //    if (exit_code >= 0) {
    //        return;
    //    }

    // TODO REMOVE
    XSetErrorHandler(XErrorHandlerImpl);
    XSetIOErrorHandler(XIOErrorHandlerImpl);

    CefSettings settings;

    settings.remote_debugging_port = 8888;  // TODO REMOVE
    CefInitialize(main_args, settings, app.get(), NULL);

    CefRunMessageLoop();
    CefShutdown();

    std::cout << "haza" << std::endl;
    return 0;
}
