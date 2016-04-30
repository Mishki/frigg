#include "client_app.h"
// #include "ClientV8ExtensionHandler.h"
//#include "MyV8Accessor.h"

ClientApp::ClientApp(std::string srv_name, std::string cli_name) {
    srv_mq = mq_open(srv_name.c_str(), O_CREAT | O_RDONLY, 0664, 0);
    if (srv_mq == (mqd_t) -1) {
        perror("server.mq_open.srv_mq");
    }

    cli_mq = mq_open(cli_name.c_str(), O_CREAT | O_WRONLY, 0664, 0);
    if (cli_mq == (mqd_t) -1) {
        perror("server.mq_open.cli_mq");
    }

    ready = event.get_future();
    thrd = std::thread(&ClientApp::mqComm, this);
}

ClientApp::~ClientApp() {
    char buf[MSG_SIZE] = {0};
    request *req = (request *) &buf;
    req->method = QUIT;

    if (mq_send(cli_mq, buf, sizeof(request), 0) == -1) {
        perror("server.mq_send.cli_mq");
    }

    if (thrd.joinable()) {
        thrd.join();
    }

    if (mq_close(srv_mq) == -1) {
        perror("server.mq_close.srv_mq");
    }

    if (mq_close(cli_mq) == -1) {
        perror("server.mq_close.cli_mq");
    }
}

void ClientApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    event.set_value(true);
}

void ClientApp::mqComm() {
    fd_set rfds;
    int nfds = std::max(srv_mq, cli_mq);

    ready.wait();
    while (true) {
        FD_ZERO(&rfds);
        FD_SET(srv_mq, &rfds);

        if (select(nfds + 1, &rfds, NULL, NULL, NULL) == -1) {
            perror("server.select");
            break;
        }

        char buf[MSG_SIZE];
        unsigned int prio;
        if (mq_receive(srv_mq, &buf[0], MSG_SIZE, &prio) != -1) {
            request *req = (request *) buf;
            std::vector<std::string> args = unparse(req->args);

            switch (req->method) {
                case QUIT:
                    CefPostTask(TID_UI, new QuitTask());
                    goto terminate;

                case SESSION:
                    CefPostTask(TID_UI, new SessionTask(
                        &handles, req->uid, cli_mq, args[0]
                    ));
                    break;

                case HTML:
                    fprintf(stderr, "HTML\n");
                    break;

                default:
                    break;
            }
        }
    }

    terminate:
    return;
}

//void ClientApp::OnContextCreated(
//    CefRefPtr<CefBrowser> browser,
//    CefRefPtr<CefFrame> frame,
//    CefRefPtr<CefV8Context> context
//) {
//
//    CEF_REQUIRE_RENDERER_THREAD();
//    CefRefPtr<CefV8Value> globe = context->GetGlobal();
//
//    CefRefPtr<CefV8Accessor> accessor = new MyV8Accessor();
//
//    CefRefPtr<CefV8Value> obj = CefV8Value::CreateObject(accessor);
//
//    //CefRefPtr<CefV8Value> str = CefV8Value::CreateString("XXXXX");
//
//    //obj->SetValue("myval", V8_ACCESS_CONTROL_DEFAULT, V8_PROPERTY_ATTRIBUTE_NONE); --> Correct one
//    obj->SetValue("myval", CefV8Value::CreateString("My String"),
//                  V8_PROPERTY_ATTRIBUTE_NONE);
//
//    globe->SetValue("myglobalvalue", obj, V8_PROPERTY_ATTRIBUTE_NONE);
//
//}
