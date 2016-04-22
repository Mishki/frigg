#ifndef LIBFRIGGA_CLIENT_APP_H_
#define LIBFRIGGA_CLIENT_APP_H_

#include "include/cef_app.h"

//ClientApp overrides CefApp and CefBrowserProcessHandler
class ClientApp : public CefApp,
                  public CefBrowserProcessHandler, //only called in broswer process. CefRenderProcessHandler is called only in render process
                  public CefRenderProcessHandler{

    public:
    ClientApp();
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {return this;}
    virtual void OnContextInitialized() OVERRIDE; //event handler fired immediately after cef software gets created: we NEED to override this
    CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
    {
        return this;
    }
//    void OnWebKitInitialized() OVERRIDE;
    virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) OVERRIDE;

private:
    IMPLEMENT_REFCOUNTING(ClientApp); //for shared reference ptrs to recount how many links to ptrs are there
};

#endif  // LIBFRIGGA_CLIENT_APP_H_

//CefRenderProcessHandler -- javascript
//GetRenderProcessHandler
