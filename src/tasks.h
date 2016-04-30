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
        std::map<int, CefRefPtr<ClientHandle>> *handles,
        char uid[37],
        mqd_t cli_mq,
        std::string url
    );
    virtual void Execute() OVERRIDE;
private:
    std::string url;
    mqd_t cli_mq;
    char uid[37];
    std::map<int, CefRefPtr<ClientHandle>> *handles;

IMPLEMENT_REFCOUNTING(SessionTask);
};

class GetHTMLTask : public virtual CefTask {
public:
    GetHTMLTask(
        std::map<int, CefRefPtr<ClientHandle>> *handles,
        char uid[37],
        mqd_t cli_mq,
        int bid
    );
    virtual void Execute() OVERRIDE;
private:
    int bid;
    mqd_t cli_mq;
    char uid[37];
    std::map<int, CefRefPtr<ClientHandle>> *handles;

IMPLEMENT_REFCOUNTING(GetHTMLTask);
};

class ExecJSTask : public virtual CefTask {
public:
    ExecJSTask(
        std::map<int, CefRefPtr<ClientHandle>> *handles,
        char uid[37],
        mqd_t cli_mq,
        int bid,
        std::string code
    );
    virtual void Execute() OVERRIDE;
private:
    std::string code;
    int bid;
    mqd_t cli_mq;
    char uid[37];
    std::map<int, CefRefPtr<ClientHandle>> *handles;

IMPLEMENT_REFCOUNTING(ExecJSTask);
};

#endif // FRIGG_TASKS_H
