#ifndef FRIGG_TASKS_H
#define FRIGG_TASKS_H

#include "include/cef_base.h"

class QuitTask : public virtual CefTask {
public:
    virtual void Execute() OVERRIDE {
        CefQuitMessageLoop();
    };
IMPLEMENT_REFCOUNTING(QuitTask);
};

//class SessionTask : public virtual CefTask {
//public:
//    virtual void Execute() OVERRIDE {
//        CefWindowInfo window_info;
//        window_info.SetAsChild(0, CefRect(0, 0, 1280, 800));  // TODO REMOVE
//        //    window_info.SetAsWindowless(0, true);  // TODO UNCOMMENT
//        CefBrowserSettings browser_settings;
//        CefRefPtr<ClientHandler> client_handler = new ClientHandler();
//
//        CefBrowserHost::CreateBrowser(
//            window_info,
//            client_handler.get(),
//            url,
//            browser_settings,
//            NULL
//        );
//    };
//IMPLEMENT_REFCOUNTING(SessionTask);
//};

#endif // FRIGG_TASKS_H
