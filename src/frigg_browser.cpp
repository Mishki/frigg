#include "frigg_browser.h"
#include "frigg_web_page.h"
#include "client_app.h"
#include "client_handler.h"
#include "include/base/cef_bind.h"

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

FriggBrowser::FriggBrowser(int argc, char *argv[]) {
    _thrd = std::thread(&FriggBrowser::run, this, argc, argv);
    std::unique_lock<std::mutex> lck(_mtx);
    while (!browser_init) {
        _cv.wait(lck);
    }

    window_info.SetAsChild(0, CefRect(0, 0, 1280, 800));  // TODO REMOVE
    //    window_info.SetAsWindowless(0, true);  // TODO UNCOMMENT
    client_handler = new ClientHandler();
}

FriggBrowser::~FriggBrowser() {
    if (_thrd.joinable()) {
        _thrd.join();
    }
}

void FriggBrowser::run(int argc, char *argv[]) {
    CefMainArgs main_args(argc, argv);

    CefRefPtr<ClientApp> app(new ClientApp(this));

    // TODO REMOVE
    XSetErrorHandler(XErrorHandlerImpl);
    XSetIOErrorHandler(XIOErrorHandlerImpl);

    CefSettings settings;
    CefString(&settings.browser_subprocess_path).FromASCII("./frigg_helper");

    settings.remote_debugging_port = 8888;  // TODO REMOVE
    CefInitialize(main_args, settings, app.get(), NULL);

    CefRunMessageLoop();
    CefShutdown();
}

FriggWebPage FriggBrowser::openUrl(const char *url) {
    CefBrowserHost::CreateBrowser(
        window_info,
        client_handler.get(),
        url,
        browser_settings,
        NULL
    );

}