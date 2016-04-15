#include "client_app.h"
#include "client_handler.h"
#include "include/wrapper/cef_helpers.h"

ClientApp::ClientApp() {}

void ClientApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    //Creates a broswer window (1 tab in reality is a browser window)

    CefWindowInfo window_info;
    window_info.SetAsWindowless(0, true); //in cef simple(the tutorial), not windowless.
    //TODO: Go through code for cefsimple

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

void ClientApp::OnWebKitInitialized() {
    std::string app_code =
                    "var app;"
                    "if (!app)"
                    "    app = {};"
                    "(function() {"
                    "    app.ChangeTextInJS = function(text) {"
                    "        native function ChangeTextInJS();"
                    "        return ChangeTextInJS(text);"
                    "    };"
                    "})();;";

    CefRegisterExtension( "v8/app", app_code, new ClientV8ExtensionHandler(this) );
}

