#ifndef FRIGGA_CLIENT_APP_H
#define FRIGGA_CLIENT_APP_H

#include "include/cef_app.h"

class ClientApp : public CefApp,
                  public CefBrowserProcessHandler,
                  public CefRenderProcessHandler {

public:
    ClientApp();

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {return this;}
    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE {return this;}

    virtual void OnContextInitialized() OVERRIDE;
//    virtual void OnContextCreated(
//        CefRefPtr<CefBrowser> browser,
//        CefRefPtr<CefFrame> frame,
//        CefRefPtr<CefV8Context> context
//    ) OVERRIDE;

private:
IMPLEMENT_REFCOUNTING(ClientApp);
};

#endif  // FRIGGA_CLIENT_APP_H
