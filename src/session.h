#ifndef FRIGG_WEB_PAGE_H
#define FRIGG_WEB_PAGE_H

#include "include/cef_browser.h"

class Session {
public:
    Session(int browser_id);
    ~Session();

    int id();
    std::string html();

private:
    int browser_id;
};

#endif // FRIGG_WEB_PAGE_H
