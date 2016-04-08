#include "client_app.h"
#include "client_handler.h"
#include "include/wrapper/cef_helpers.h"

ClientApp::ClientApp() {}

void ClientApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();

    CefWindowInfo window_info;
    window_info.SetAsWindowless(0, true);

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
