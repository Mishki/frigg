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
    if (name == "myval") {
      if (value.IsString()) {
        // Store the value.
        myval_ = value.GetStringValue();
      } else {
        // Throw an exception.
        exception = "Invalid value type";
      }
      return true;
    }

    // Value does not exist.
    return false;
  }

  // Variable used for storing the value.
  CefString myval_;

  // Provide the reference counting implementation for this class.
  IMPLEMENT_REFCOUNTING(MyV8Accessor);
};
