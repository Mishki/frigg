#ifndef FRIGG_CLIENT_APP_H
#define FRIGG_CLIENT_APP_H

#include "include/cef_app.h"
#include "frigg_browser.h"

class ClientApp : public CefApp,
                  public CefBrowserProcessHandler,
                  public CefRenderProcessHandler {
public:
    ClientApp(FriggBrowser *frigg = NULL);

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {return this;}
    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE {return this;}

    virtual void OnContextInitialized() OVERRIDE;
    //    virtual void OnContextCreated(
    //        CefRefPtr<CefBrowser> browser,
    //        CefRefPtr<CefFrame> frame,
    //        CefRefPtr<CefV8Context> context
    //    ) OVERRIDE;

private:
    FriggBrowser *frigg;

IMPLEMENT_REFCOUNTING(ClientApp);
};

#endif  // FRIGG_CLIENT_APP_H
