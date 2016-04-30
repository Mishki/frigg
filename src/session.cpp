#include "session.h"

Session::Session(int browser_id) {
    this->browser_id = browser_id;
}

Session::~Session() {

}

int Session::id() {
    return browser_id;
}

std::string Session::html() {

}







