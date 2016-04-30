#include "session.h"

Session::Session(std::map<std::string, std::promise<long>> *promises, mqd_t srv_mq, int bid) {
    this->bid = bid;
    this->promises = promises;
    this->srv_mq = srv_mq;
}

Session::~Session() {

}

int Session::getBid() {
    return bid;
}

std::string Session::html() {
    char buf[MSG_SIZE];
    uuid_t uuid = {0};
    uuid_generate(uuid);
    request *req = (request *) buf;
    uuid_unparse_lower(uuid, req->uid);
    req->method = HTML;

    int size = parse(req->args, 1, std::to_string(bid));

    if (mq_send(srv_mq, buf, sizeof(request) + size, 0) == -1) {
        perror("client.mq_send.srv_mq");
    }

    (*promises)[req->uid] = std::promise<long>();
    std::future<long> fut = (*promises)[req->uid].get_future();
    fut.wait();

}









