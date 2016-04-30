#ifndef FRIGG_ASYNC_STRING_H
#define FRIGG_ASYNC_STRING_H

#include <mqueue.h>
#include "include/cef_client.h"

class HtmlVisitor : public CefStringVisitor {

    public:
    HtmlVisitor(char uid[37], mqd_t cli_mq);
    virtual void Visit(const CefString& string) OVERRIDE;

private:
    mqd_t cli_mq;
    char uid[37];

    IMPLEMENT_REFCOUNTING(HtmlVisitor);
};


#endif // FRIGG_ASYNC_STRING_H
