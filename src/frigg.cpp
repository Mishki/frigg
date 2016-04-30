#include "frigg.h"

// TODO REMOVE
namespace {

    int XErrorHandlerImpl(Display *display, XErrorEvent *event) {
        LOG(WARNING)
        << "X error received: "
        << "type " << event->type << ", "
        << "serial " << event->serial << ", "
        << "error_code " << static_cast<int>(event->error_code) << ", "
        << "request_code " << static_cast<int>(event->request_code) << ", "
        << "minor_code " << static_cast<int>(event->minor_code);
        return 0;
    }

    int XIOErrorHandlerImpl(Display *display) {
        return 0;
    }

}

Browser::Browser(int argc, char *argv[]) {
    uuid_t uuid = {0};

    uuid_generate(uuid);
    char srv_uuid[37];
    uuid_unparse_lower(uuid, srv_uuid);
    std::string srv_name = "/" + std::string(srv_uuid);

    uuid_generate(uuid);
    char cli_uuid[37];
    uuid_unparse_lower(uuid, cli_uuid);
    std::string cli_name = "/" + std::string(cli_uuid);

    if ((cef_pid = fork()) == -1) {
        perror("client.fork");
        _exit(EXIT_FAILURE);
    } else if (cef_pid == 0) {
        CefMainArgs main_args(argc, argv);
        CefRefPtr<ClientApp> app(new ClientApp(srv_name, cli_name));

        // TODO REMOVE
        XSetErrorHandler(XErrorHandlerImpl);
        XSetIOErrorHandler(XIOErrorHandlerImpl);

        CefSettings settings;
        CefString(&settings.browser_subprocess_path).FromASCII("./helper");

        std::random_device rd;
        std::uniform_int_distribution<int> dist(49152, 65535);
        int port = dist(rd);

        LOG(INFO) << "debbuging on port: " << port;
        settings.remote_debugging_port = port;
        CefInitialize(main_args, settings, app.get(), NULL);

        CefRunMessageLoop();
        CefShutdown();
        app.get()->~ClientApp();
        _exit(EXIT_SUCCESS);
    }

    srv_mq = mq_open(srv_name.c_str(), O_CREAT | O_WRONLY, 0664, 0);
    if (srv_mq == (mqd_t) -1) {
        perror("client.mq_open.srv_mq\n");
    }

    cli_mq = mq_open(cli_name.c_str(), O_CREAT | O_RDONLY, 0664, 0);
    if (cli_mq == (mqd_t) -1) {
        perror("client.mq_open.cli_mq");
    }

    thrd = std::thread(&Browser::mqComm, this);


    //    char buf[MSG_SIZE] = {0};
    //    request *req = (request *)&buf;
    //    req->method = INIT;
    //
    //    if (mq_send(srv_mq, buf, sizeof(request), 0) == -1) {
    //        perror("client.mq_send.srv_mq");
    //    }

}

Browser::~Browser() {
    char buf[MSG_SIZE] = {0};
    request *req = (request *) &buf;
    req->method = QUIT;

    if (mq_send(srv_mq, buf, sizeof(request), 0) == -1) {
        perror("client.mq_send.srv_mq");
    }

    if (thrd.joinable()) {
        thrd.join();
    }

    if (mq_close(srv_mq) == -1) {
        perror("client.mq_close.srv_mq");
    }

    if (mq_close(cli_mq) == -1) {
        perror("client.mq_close.cli_mq");
    }
}

void Browser::mqComm() {
    fd_set rfds;
    int nfds = std::max(srv_mq, cli_mq);
    while (true) {
        FD_ZERO(&rfds);
        FD_SET(cli_mq, &rfds);

        if (select(nfds + 1, &rfds, NULL, NULL, NULL) == -1) {
            perror("client.select");
            break;
        }

        char buf[MSG_SIZE];
        unsigned int prio;
        if (mq_receive(cli_mq, &buf[0], MSG_SIZE, &prio) != -1) {
            request *req = (request *) buf;
            switch (req->method) {
                case QUIT:
                    CefQuitMessageLoop();
                    goto terminate;

                default:
                    break;
            }
        }
    }

    terminate:
    return;
}

//Session Browser::tab(std::string url) {
//    char buf[MSG_SIZE] = {0};
//    request *req = (request *)&buf;
//    req->method = SESSION;
//
//    if (mq_send(srv_mq, buf, sizeof(request), 0) == -1) {
//        perror("client.mq_send.srv_mq");
//    }
//
//
//    return Session(future.get());
//}