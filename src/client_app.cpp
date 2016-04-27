#include <iostream>
#include "client_app.h"
#include "client_handler.h"
#include "include/wrapper/cef_helpers.h"
// #include "ClientV8ExtensionHandler.h"
//#include "MyV8Accessor.h"

ClientApp::ClientApp() {}

void ClientApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

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

//void ClientApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
//                                 CefRefPtr<CefFrame> frame,
//                                 CefRefPtr<CefV8Context> context) {
//
//    CEF_REQUIRE_RENDERER_THREAD();
//    CefRefPtr<CefV8Value> globe = context->GetGlobal();
//
//    CefRefPtr<CefV8Accessor> accessor = new MyV8Accessor();
//
//    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(accessor);
//
//    //CefRefPtr<CefV8Value> str = CefV8Value::CreateString("XXXXX");
//
//    //obj->SetValue("myval", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE); --> Correct one
//    obj->SetValue("myval", CefV8Value::CreateString("My String"),
//                  V8_PROPERTY_ATTRIBUTE_NONE);
//
//    globe->SetValue("myglobalvalue", obj, V8_PROPERTY_ATTRIBUTE_NONE);
//
//}
