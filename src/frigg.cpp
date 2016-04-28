#include "frigg.h"
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
    while (!initialized) {
        _cv.wait(lck);
    }
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

class MyTask : public virtual CefTask {
public:
    MyTask() {}
    virtual void Execute() OVERRIDE {
        CefWindowInfo window_info;
        window_info.SetAsChild(0, CefRect(0, 0, 1280, 800));  // TODO REMOVE
        //    window_info.SetAsWindowless(0, true);  // TODO UNCOMMENT
        CefBrowserSettings browser_settings;
        CefRefPtr<ClientHandler> client_handler(new ClientHandler());

        CefBrowserHost::CreateBrowser(
            window_info,
            client_handler.get(),
            "http://www.google.com",
            browser_settings,
            NULL
        );
    }

IMPLEMENT_REFCOUNTING(MyTask);
};

void FriggBrowser::openUrl(const char *url) {
    printf("%s\n", url);


    //    base::Bind(&MyFunc, 23, "hello world");

    CefPostTask(TID_UI, new MyTask());

}

void FriggBrowser::initializer() {
    std::unique_lock<std::mutex> lck(_mtx);
    initialized = true;
    _cv.notify_all();
}






