#include "client_app.h"
#include <X11/Xlib.h>
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

int main(int argc, char *argv[]) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr<ClientApp> app(new ClientApp);

    int exit_code = CefExecuteProcess(main_args, app.get(), NULL);
    if (exit_code >= 0) {
        return exit_code;
    }

    // TODO REMOVE
    XSetErrorHandler(XErrorHandlerImpl);
    XSetIOErrorHandler(XIOErrorHandlerImpl);

    CefSettings settings;
    settings.remote_debugging_port = 8888;  // TODO REMOVE
    CefInitialize(main_args, settings, app.get(), NULL);

    //Simplest way to execute JS from a client application
    //    CefRefPtr<CefBrowser> browser;
    //    CefRefPtr<CefFrame> frame = browser ->GetMainFrame();
    //    frame -> ExecuteJavaScript("alert('ExecuteJavascript Works!!');",
    //            frame -> GetURL(), 0);

    CefRunMessageLoop();
    CefShutdown();
    return 0;
}
