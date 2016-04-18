#include <iostream>
#include "client_handler.h"
#include "async_string.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"

/*
#include "include/cef_app.h"
#include "include/cef_base.h"
#include "include/cef_client.h"
#include "include/cef_command_line.h"
#include "include/cef_frame.h"
//#include "include/cef_runnable.h"
#include "include/cef_web_plugin.h"
*/
namespace {
ClientHandler *g_instance = NULL;
}

ClientHandler::ClientHandler() {
    DCHECK(!g_instance);
    g_instance = this;
}

ClientHandler::~ClientHandler() {
    g_instance = NULL;
}

//Right after browser window is created
void ClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    if ( !m_Browser.get() ) {
        // We need to keep the main child window, but not popup windows
        m_Browser     = browser;
        m_BrowserHwnd = browser->GetHost()->GetWindowHandle();
    }

    browser_list_.push_back(browser); //push browser handler onto main list of browsers
}

bool ClientHandler::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    return false;
}

//removes browser window from list, and if empty, fires quit message
//This quits the Cef message loop and exits the application
void ClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    BrowserList::iterator bit = browser_list_.begin();
    for (; bit != browser_list_.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browser_list_.erase(bit);
            break;
        }
    }

    if (browser_list_.empty()) {
        CefQuitMessageLoop();
    }
}

//loading for each separate frame in browser
void ClientHandler::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) {
    CEF_REQUIRE_UI_THREAD();

    if (frame->IsMain()) {
        frame->ExecuteJavaScript("document.body.innerHTML = window.myval;", frame->GetURL(), 0);

        std::cout << "Status Code: " << httpStatusCode << std::endl;
        frame->GetSource(new AsyncString()); //Ajax request, to wait for code once requested
    }
}
//rectanlge printable space of browser
bool ClientHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
    rect = CefRect(0, 0, RENDER_WIDTH, RENDER_HEIGHT);
    return true;
}
void ClientHandler::OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyRects, const void *buffer, int width, int height) {

}
