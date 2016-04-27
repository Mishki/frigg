#ifndef FRIGGA_ASYNC_STRING_H
#define FRIGGA_ASYNC_STRING_H

#include "include/cef_client.h"

class AsyncString : public CefStringVisitor {

    public:
    AsyncString();
    virtual void Visit(const CefString& string) OVERRIDE;

    IMPLEMENT_REFCOUNTING(AsyncString);
};


#endif // FRIGGA_ASYNC_STRING_H
