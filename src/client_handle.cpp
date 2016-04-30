#include <iostream>
#include "client_handle.h"
#include "async_string.h"
#include "include/cef_app.h"
#include "include/wrapper/cef_helpers.h"
#include "include/base/cef_logging.h"
#include "request.h"


namespace {
    ClientHandle *g_instance = NULL;
}

ClientHandle::ClientHandle() {
    DCHECK(!g_instance);
    g_instance = this;
}

ClientHandle::ClientHandle(char bid[37], char uid[37], mqd_t cli_mq) {
    DCHECK(!g_instance);
    g_instance = this;

    this->cli_mq = cli_mq;
    memcpy(this->bid, bid, 37);
    memcpy(this->uid, uid, 37);
}

ClientHandle::~ClientHandle() {
    g_instance = NULL;
}

void ClientHandle::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    browser_list.push_back(browser);
}

bool ClientHandle::DoClose(CefRefPtr<CefBrowser> browser) {
    CEF_REQUIRE_UI_THREAD();
    return false;
}

void ClientHandle::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
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

void ClientHandle::OnLoadEnd(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    int httpStatusCode
) {
    CEF_REQUIRE_UI_THREAD();
    char buf[MSG_SIZE];
    request *req = (request *) buf;
    memcpy(req->uid, this->uid, 37);
    req->method = SESSION;
    int size = parse(req->args, 2, bid, std::to_string(httpStatusCode).c_str());

    if (mq_send(cli_mq, buf, sizeof(request) + size, 0) == -1) {
        perror("client.mq_send.srv_mq");
    }


    //    if (frame->IsMain()) {
    //        frame->ExecuteJavaScript("window.blue = 12345;", frame->GetURL(), 0);
    //        std::cout << "Status Code: " << httpStatusCode << std::endl;
    //        frame->GetSource(new AsyncString());
    //    }
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
