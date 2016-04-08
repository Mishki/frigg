#include "client_app.h"

int main(int argc, char *argv[]) {
    CefMainArgs main_args(argc, argv);
    CefRefPtr <ClientApp> app(new ClientApp);

    int exit_code = CefExecuteProcess(main_args, app.get(), NULL);
    if (exit_code >= 0) {
        return exit_code;
    }

    CefSettings settings;
    CefInitialize(main_args, settings, app.get(), NULL);

    CefRunMessageLoop();
    CefShutdown();
    return 0;
}
