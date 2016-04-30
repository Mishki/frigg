#include "tasks.h"
#include "html_visitor.h"

void QuitTask::Execute() {
    CefQuitMessageLoop();
}

SessionTask::SessionTask(
    std::map<int, CefRefPtr<ClientHandle>> *handles,
    char uid[37],
    mqd_t cli_mq,
    std::string url
) {
    this->url = url;
    memcpy(this->uid, uid, 37);
    this->cli_mq = cli_mq;
    this->handles = handles;
}

void SessionTask::Execute() {
    CefWindowInfo window_info;
    window_info.SetAsChild(0, CefRect(0, 0, 1280, 800));  // TODO REMOVE
    //    window_info.SetAsWindowless(0, true);  // TODO UNCOMMENT
    CefBrowserSettings browser_settings;
    CefRefPtr<ClientHandle> handle(new ClientHandle(uid, cli_mq));

    CefRefPtr<CefBrowser> browser = CefBrowserHost::CreateBrowserSync(
        window_info,
        handle.get(),
        url,
        browser_settings,
        NULL
    );

    int bid = browser->GetIdentifier();
    (*handles)[bid] = handle;
}


GetHTMLTask::GetHTMLTask(
    std::map<int, CefRefPtr<ClientHandle>> *handles,
    char uid[37],
    mqd_t cli_mq,
    int bid
) {
    memcpy(this->uid, uid, 37);
    this->cli_mq = cli_mq;
    this->handles = handles;
    this->bid = bid;
}

void GetHTMLTask::Execute() {
    CefRefPtr<CefBrowser> browser = (*handles)[bid].get()->getMainBrowser();
    browser.get()->GetMainFrame()->GetSource(new HtmlVisitor(uid, cli_mq));
}

ExecJSTask::ExecJSTask(
    std::map<int, CefRefPtr<ClientHandle>> *handles,
    char *uid,
    mqd_t cli_mq,
    int bid,
    std::string code
) {
    memcpy(this->uid, uid, 37);
    this->cli_mq = cli_mq;
    this->handles = handles;
    this->bid = bid;
    this->code = code;
}
void ExecJSTask::Execute() {
    fprintf(stderr, "JS RUNNING\n");

    CefRefPtr<CefBrowser> browser = (*handles)[bid].get()->getMainBrowser();
    CefString url = browser.get()->GetMainFrame()->GetURL();
    browser.get()->GetMainFrame()->ExecuteJavaScript(code, url, 0);

    char buf[MSG_SIZE];
    request *req = (request *) buf;
    memcpy(req->uid, this->uid, 37);
    req->method = JS;

    if (mq_send(cli_mq, buf, sizeof(request), 0) == -1) {
        perror("client.mq_send.srv_mq");
    }
}



