#ifndef FRIGG_CLIENT_APP_H
#define FRIGG_CLIENT_APP_H

#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include "frigg.h"
#include "tasks.h"
#include "request.h"
#include "client_handle.h"
#include <future>

class ClientApp : public CefApp,
                  public CefBrowserProcessHandler,
                  public CefRenderProcessHandler {
    friend class SessionTask;

public:
    ClientApp() {};
    ClientApp(std::string srv_name, std::string cli_name);
    ~ClientApp();

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {return this;}
    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE {return this;}

    virtual void OnContextInitialized() OVERRIDE;
    //    virtual void OnContextCreated(
    //        CefRefPtr<CefBrowser> browser,
    //        CefRefPtr<CefFrame> frame,
    //        CefRefPtr<CefV8Context> context
    //    ) OVERRIDE;

private:
    void mqComm();

    std::thread thrd;
    mqd_t srv_mq, cli_mq;
    std::promise<bool> event;
    std::future<bool> ready;
    std::map<int, CefRefPtr<ClientHandle>> handles;

IMPLEMENT_REFCOUNTING(ClientApp);
};

#endif  // FRIGG_CLIENT_APP_H
