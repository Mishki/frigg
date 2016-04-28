#ifndef FRIGG_CREATE_BROWSER_TASK_H
#define FRIGG_CREATE_BROWSER_TASK_H

#include <include/cef_task.h>
#include <uuid/uuid.h>
#include "frigg_browser.h"

class CreateBrowserTask : public virtual CefTask {
public:
    CreateBrowserTask(FriggBrowser *frigg, const char *url, uuid_t uuid);
    ~CreateBrowserTask();

    virtual void Execute() OVERRIDE;

private:
    FriggBrowser *frigg;
    std::string url;
    uuid_t uuid;

IMPLEMENT_REFCOUNTING(CreateBrowserTask);
};

#endif //FRIGG_CREATE_BROWSER_TASK_H
