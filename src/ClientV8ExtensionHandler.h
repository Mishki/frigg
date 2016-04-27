#ifndef FRIGGA_CLIENTV8EXTENSIONHANDLER_H
#define FRIGGA_CLIENTV8EXTENSIONHANDLER_H


#include "include/cef_app.h"

struct ClientV8ExtensionHandler : public CefV8Handler {
    ClientV8ExtensionHandler(CefRefPtr<CefApp> app);

    bool Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments, CefRefPtr<CefV8Value> &retval, CefString &exception) OVERRIDE;

private:
    CefRefPtr<CefApp> app;

IMPLEMENT_REFCOUNTING(ClientV8ExtensionHandler);
};

#endif // FRIGGA_CLIENTV8EXTENSIONHANDLER_H