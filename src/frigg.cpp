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

Browser::Browser() {
    int srv_pipe[2];
    if (pipe(srv_pipe) == -1) {
        perror("client.pipe(srv_pipe) failed");
    }

    int cli_pipe[2];
    if (pipe(cli_pipe) == -1) {
        perror("client.pipe(cli_pipe) failed");
    }

    if ((cef_pid = fork()) == -1) {
        perror("client.fork() failed");
        std::exit(EXIT_FAILURE);
    } else if (cef_pid == 0) {
        close(srv_pipe[1]);
        close(cli_pipe[0]);

        CefMainArgs main_args(argc, argv);
        CefRefPtr<ClientApp> app(new ClientApp(srv_pipe[0], cli_pipe[1]));

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
        std::exit(EXIT_SUCCESS);
    }

    close(srv_pipe[0]);
    srv_fd = srv_pipe[1];

    close(cli_pipe[1]);
    cli_fd = cli_pipe[0];

    thrd = std::thread(&Browser::ipc_loop, this);
}

Browser::~Browser() {
//    char buf[MSG_SIZE];
//    uuid_t uuid = {0};
//    uuid_generate(uuid);
//    request *req = (request *) buf;
//    uuid_unparse_lower(uuid, req->uid);
//    req->method = QUIT;
//
//    if (mq_send(srv_mq, buf, sizeof(request), 0) == -1) {
//        perror("client.mq_send.srv_mq");
//    }

    if (thrd.joinable()) {
        thrd.join();
    }

    close(srv_fd);
    close(cli_fd);
}

void Browser::ipc_loop() {
    fd_set rfds;
    while (true) {
        FD_ZERO(&rfds);
        FD_SET(cli_fd, &rfds);

        if (select(cli_fd + 1, &rfds, NULL, NULL, NULL) == -1) {
            perror("client.select()");
            break;
        }

        char buf[MSG_SIZE];
        unsigned int prio;
        if (mq_receive(cli_mq, &buf[0], MSG_SIZE, &prio) != -1) {
            request *req = (request *) buf;
            std::vector<std::string> args = unparse(req->args);
            switch (req->method) {
                case QUIT:
                    CefQuitMessageLoop();
                    goto terminate;

                case SESSION:
                    promises[req->uid].set_value(std::stol(args[0].c_str()));
                    break;

                case HTML:
//                    promises[req->uid].set_value(req->shmem);
                    break;

                case JS:
                    promises[req->uid].set_value(1);
                    break;

                default:
                    break;
            }
        }
    }

    terminate:
    return;
}

Session Browser::tab(std::string url) {
    char buf[MSG_SIZE];
    uuid_t uuid = {0};
    uuid_generate(uuid);
    request *req = (request *) buf;
    uuid_unparse_lower(uuid, req->uid);
    req->method = SESSION;

    int size = parse(req->args, 1, url.c_str());

    if (mq_send(srv_mq, buf, sizeof(request) + size, 0) == -1) {
        perror("client.mq_send.srv_mq");
    }

    promises[req->uid] = std::promise<long>();
    std::future<long> fut = promises[req->uid].get_future();
    fut.wait();

    return Session(&promises, srv_mq, (int) fut.get());
}