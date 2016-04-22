//
// Created by sania on 4/14/16.
//

#ifndef LIBFRIGGA_CLIENTV8EXTENSIONHANDLER_H
#define LIBFRIGGA_CLIENTV8EXTENSIONHANDLER_H
//#ifndef __CEF3SimpleSample__ClientV8ExtensionHandler__
//#define __CEF3SimpleSample__ClientV8ExtensionHandler__


#include "include/cef_app.h"

struct ClientV8ExtensionHandler : public CefV8Handler {
    ClientV8ExtensionHandler(CefRefPtr<CefApp> app);

    bool Execute(const CefString &name, CefRefPtr<CefV8Value> object, const CefV8ValueList &arguments, CefRefPtr<CefV8Value> &retval, CefString &exception) OVERRIDE;

private:
    CefRefPtr<CefApp> app;

IMPLEMENT_REFCOUNTING(ClientV8ExtensionHandler);
};

#endif //LIBFRIGGA_CLIENTV8EXTENSIONHANDLER_H


//#endif /* defined(__CEF3SimpleSample__ClientV8ExtensionHandler__) */