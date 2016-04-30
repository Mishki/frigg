#ifndef FRIGG_TASKS_H
#define FRIGG_TASKS_H

#include "request.h"
#include <uuid/uuid.h>
#include "client_handle.h"
#include <include/cef_app.h>
#include <mqueue.h>

class QuitTask : public virtual CefTask {
public:
    virtual void Execute() OVERRIDE;
IMPLEMENT_REFCOUNTING(QuitTask);
};

class SessionTask : public virtual CefTask {
public:
    SessionTask(
        std::map<std::string, CefRefPtr<ClientHandle>> *handles,
        char uid[37],
        mqd_t cli_mq,
        std::string url
    );
    virtual void Execute() OVERRIDE;
private:
    std::string url;
    mqd_t cli_mq;
    char uid[37];
    std::map<std::string, CefRefPtr<ClientHandle>> *handles;

IMPLEMENT_REFCOUNTING(SessionTask);
};

#endif // FRIGG_TASKS_H
