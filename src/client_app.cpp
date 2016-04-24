#include "client_app.h"
#include "client_handler.h"
#include "include/wrapper/cef_helpers.h"
// #include "ClientV8ExtensionHandler.h"
#include "MyV8Accessor.h"

ClientApp::ClientApp() {}

void ClientApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    //Creates a broswer window (1 tab in reality is a browser window)

    CefWindowInfo window_info;

    window_info.SetAsWindowless(0, true); //in cef simple(the tutorial), not windowless.
//
    CefBrowserSettings browser_settings; //class
    //creating a singleton instance of ClientHandler
    //All browsers share this ClientHandler instance which is responsible for customizing browser behavior
    //and handling browser-related callbacks
    CefRefPtr<ClientHandler> client_handler(new ClientHandler()); //overriding to deal with other events

    //creating a browser window
    CefBrowserHost::CreateBrowser(
        window_info,
        client_handler.get(),
        "http://www.google.com",
        browser_settings,
        NULL
    );
}

//void ClientApp::OnWebKitInitialized() {
//    // all js execution takes place on this thread
//    CEF_REQUIRE_RENDERER_THREAD();
//
//    std::string app_code =
//                    "var app;"
//                    "if (!app)"
//                    "    app = {};"
//                    "(function() {"
//                    "    app.ChangeTextInJS = function(text) {"
//                    "        native function ChangeTextInJS();"
//                    "        return ChangeTextInJS(text);"
//                    "    };"
//                    "})();;";
//
//    CefRegisterExtension( "v8/app", app_code, new ClientV8ExtensionHandler(this) );
//}
//Window binding: To attach values to a frame's window object
void ClientApp::OnContextCreated(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) {

    // all js execution takes place on this thread
    CEF_REQUIRE_RENDERER_THREAD();
    // Retrieve the context's window object.
    CefRefPtr<CefV8Value> globe = context->GetGlobal();

    // create accessor to obj
    CefRefPtr<CefV8Accessor> accessor = new MyV8Accessor();

    // Create a new V8 string value. See the "Basic JS Types" section below.
    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(accessor);

    //CefRefPtr<CefV8Value> str = CefV8Value::CreateString("XXXXX");

    //setting value to the JS object we created
    //obj->SetValue("myval", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE); --> Correct one
    obj -> SetValue("myval", CefV8Value::CreateString("My String"), V8_PROPERTY_ATTRIBUTE_NONE);

    //Add the object to the window as "window.myglobalvalue"
    globe->SetValue("myglobalvalue", obj, V8_PROPERTY_ATTRIBUTE_NONE);

}
