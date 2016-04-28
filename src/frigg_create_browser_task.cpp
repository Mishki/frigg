#include "frigg_create_browser_task.h"

CreateBrowserTask::CreateBrowserTask(
    FriggBrowser *frigg,
    const char *url,
    uuid_t uuid
) {
    this->frigg = frigg;
    this->url = url;
    uuid_copy(this->uuid, uuid);
}
CreateBrowserTask::~CreateBrowserTask() {
    this->frigg = NULL;
}
void CreateBrowserTask::Execute() {
    CefRefPtr<CefBrowser> browser = CefBrowserHost::CreateBrowserSync(
        frigg->window_info,
        frigg->client_handler.get(),
        url,
        frigg->browser_settings,
        NULL
    );
}





