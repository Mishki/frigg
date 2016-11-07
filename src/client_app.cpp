#include "client_app.h"
// #include "ClientV8ExtensionHandler.h"
//#include "MyV8Accessor.h"

ClientApp::ClientApp(int srv_fd, int cli_fd) {
    this->srv_fd = srv_fd;
    this->cli_fd = cli_fd;

    if (std::atexit(ClientApp::~ClientApp) != 0) {
        perror("std::atexit(ClientApp::~ClientApp) failed");
        std::exit(EXIT_FAILURE);
    }

    ready = event.get_future();
    thrd = std::thread(&ClientApp::ipc_loop, this);
}

ClientApp::~ClientApp() {
//    char buf[MSG_SIZE] = {0};
//    request *req = (request *) &buf;
//    req->method = QUIT;
//
//    if (mq_send(cli_mq, buf, sizeof(request), 0) == -1) {
//        perror("server.mq_send.cli_mq");
//    }

    if (thrd.joinable()) {
        thrd.join();
    }

    close(srv_fd);
    close(cli_fd);
}

void ClientApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    event.set_value(true);
}

void ClientApp::ipc_loop() {
    fd_set rfds;
    ready.wait();
    while (true) {
        FD_ZERO(&rfds);
        FD_SET(srv_fd, &rfds);

        if (select(srv_fd + 1, &rfds, NULL, NULL, NULL) == -1) {
            perror("server.select()");
            break;
        }

        char buf[MSG_SIZE];
        if (read(srv_fd, &buf[0], MSG_SIZE) != -1) {
            write(cli_fd, buf, MSG_SIZE);
//            request *req = (request *) buf;
//            std::vector<std::string> args = unparse(req->args);
//
//            switch (req->method) {
//                case QUIT:
//                    CefPostTask(TID_UI, new QuitTask());
//                    goto terminate;
//
//                case SESSION:
//                    CefPostTask(TID_UI, new SessionTask(
//                        &handles, req->uid, cli_mq, args[0]
//                    ));
//                    break;
//
//                case HTML:
//                    CefPostTask(TID_UI, new GetHTMLTask(
//                        &handles, req->uid, cli_mq, std::stoi(args[0])
//                    ));
//                    break;
//
//                case JS:
//                    CefPostTask(TID_UI, new ExecJSTask(
//                        &handles, req->uid, cli_mq, std::stoi(args[0]), args[1]
//                    ));
//                    break;
//
//                default:
//                    break;
//            }
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
