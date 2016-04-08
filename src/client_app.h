#ifndef LIBFRIGGA_CLIENT_APP_H_
#define LIBFRIGGA_CLIENT_APP_H_

#include "include/cef_app.h"

class ClientApp : public CefApp,
                  public CefBrowserProcessHandler {
    public:
    ClientApp();
    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {return this;}
    virtual void OnContextInitialized() OVERRIDE;

    private:
    IMPLEMENT_REFCOUNTING(ClientApp);
};

#endif  // LIBFRIGGA_CLIENT_APP_H_