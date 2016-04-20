#include "include/cef_v8.h"

class MyV8Accessor : public CefV8Accessor {
    public:
    MyV8Accesor();
    ~MyV8Accessor();

    virtual bool Get(const CefString& name,
                     const CefRefPtr<CefV8Value> object,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception) OVERRIDE { return this; }
    virtual bool Set(const CefString& name,
                     const CefRefPtr<CefV8Value> object,
                     const CefRefPtr<CefV8Value> value,
                     CefString& exception) OVERRIDE { return this; }
    protected:
    CefString myval_;

    IMPLEMENT_REFCOUNTING(MyV8Accessor);
};
