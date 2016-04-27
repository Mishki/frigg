#ifndef LIBFRIGGA_MYV8ACCESSOR_H
#define LIBFRIGGA_MYV8ACCESSOR_H

#include "include/cef_v8.h"
class MyV8Accessor : public CefV8Accessor {
public:
    MyV8Accessor() {}

    virtual bool Get(const CefString& name,
                     const CefRefPtr<CefV8Value> object,
                     CefRefPtr<CefV8Value>& retval,
                     CefString& exception) OVERRIDE {
        if (name == "myval") {
            // Return the value.
            retval = CefV8Value::CreateString(myval_);
            return true;
        }

        // Value does not exist.
        return false;
    }

    virtual bool Set(const CefString& name,
                     const CefRefPtr<CefV8Value> object,
                     const CefRefPtr<CefV8Value> value,
                     CefString& exception) OVERRIDE {
        CefV8Value *valueCopy = value.get();
        if (name == "myval") {
            if (valueCopy->IsString()) {
                // Store the value.
                myval_ = valueCopy->GetStringValue();
            } else {
                // Throw an exception.
                exception = "Invalid value type";
            }
            return true;
        }

        }

        // Value does not exist.
        return false;
    }

    // Variable used for storing the value.
    CefString myval_;

    // Provide the reference counting implementation for this class.
IMPLEMENT_REFCOUNTING(MyV8Accessor);
};


#endif //LIBFRIGGA_MYV8ACCESSOR_H
