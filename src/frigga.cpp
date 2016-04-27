#include "frigga.h"
#include "client_app.h"

#include <X11/Xlib.h>
#include <iostream>
#include <exception>
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

Frigga::Frigga(int argc, char *argv[]) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr<ClientApp> app(new ClientApp);

//    int exit_code = CefExecuteProcess(main_args, app.get(), NULL);
//    if (exit_code >= 0) {
//        throw std::runtime_error("failed (exit_code >= 0)");
//    }

    // TODO REMOVE
    XSetErrorHandler(XErrorHandlerImpl);
    XSetIOErrorHandler(XIOErrorHandlerImpl);

    CefSettings settings;
    CefString(&settings.browser_subprocess_path).FromASCII("./frigga_helper");

    settings.remote_debugging_port = 8888;  // TODO REMOVE
    CefInitialize(main_args, settings, app.get(), NULL);

    CefRunMessageLoop();
    CefShutdown();

    std::cout << "haza" << std::endl;
}
Frigga::~Frigga() {}
