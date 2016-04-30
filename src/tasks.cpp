#include "tasks.h"

void QuitTask::Execute() {
    CefQuitMessageLoop();
}

SessionTask::SessionTask(
    std::map<std::string, CefRefPtr<ClientHandle>> *handles,
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
    uuid_t uuid = {0};
    uuid_generate(uuid);
    char bid[37];
    uuid_unparse_lower(uuid, bid);

    CefWindowInfo window_info;
    window_info.SetAsChild(0, CefRect(0, 0, 1280, 800));  // TODO REMOVE
    //    window_info.SetAsWindowless(0, true);  // TODO UNCOMMENT
    CefBrowserSettings browser_settings;
    CefRefPtr<ClientHandle> handle(new ClientHandle(bid, uid, cli_mq));

    CefBrowserHost::CreateBrowserSync(
        window_info,
        handle.get(),
        url,
        browser_settings,
        NULL
    );

    (*handles)[bid] = handle;
}

