#include <iostream>
#include "async_string.h"

void AsyncString::Visit(const CefString &string) {
    printf("%s\n", string.ToString().c_str());
    //    CefQuitMessageLoop();
}






