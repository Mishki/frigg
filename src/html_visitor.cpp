#include <iostream>
#include <include/cef_app.h>
#include "html_visitor.h"
#include "request.h"

HtmlVisitor::HtmlVisitor(char *uid, mqd_t cli_mq) {
    memcpy(this->uid, uid, 37);
    this->cli_mq = cli_mq;
}

void HtmlVisitor::Visit(const CefString &string) {
//    fprintf(stderr, "%s\n", string.ToString().c_str());

    char buf[MSG_SIZE];
    request *req = (request *) buf;
    memcpy(req->uid, this->uid, 37);
    req->method = HTML;

    if (mq_send(cli_mq, buf, sizeof(request), 0) == -1) {
        perror("client.mq_send.srv_mq");
    }
}









