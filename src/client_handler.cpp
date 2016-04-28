#include <iostream>
#include "client_handler.h"
#include "async_string.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"


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

void ClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    browser_list.push_back(browser);

    printf("size: %d\n", (int) browser_list.size());
}

bool ClientHandler::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    return false;
}

void ClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();

    BrowserList::iterator bit = browser_list.begin();
    for (; bit != browser_list.end(); ++bit) {
        if ((*bit)->IsSame(browser)) {
            browser_list.erase(bit);
            break;
        }
    }

    if (browser_list.empty()) {
        CefQuitMessageLoop();
    }
}

void ClientHandler::OnLoadEnd(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    int httpStatusCode
) {
    CEF_REQUIRE_UI_THREAD();

    if (frame->IsMain()) {
        frame->ExecuteJavaScript("window.blue = 12345;", frame->GetURL(), 0);
        std::cout << "Status Code: " << httpStatusCode << std::endl;
//        frame->GetSource(new AsyncString());
    }
}

//bool ClientHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
//    rect = CefRect(0, 0, RENDER_WIDTH, RENDER_HEIGHT);
//    return true;
//}
//
//void ClientHandler::OnPaint(CefRefPtr<CefBrowser> browser,
//                            CefRenderHandler::PaintElementType type,
//                            const CefRenderHandler::RectList &dirtyRects,
//                            const void *buffer, int width, int height) {
//
//}
