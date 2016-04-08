#ifndef LIBFRIGGA_CLIENT_HANDLER_H_
#define LIBFRIGGA_CLIENT_HANDLER_H_

#include "include/cef_client.h"

#include <list>

#define RENDER_WIDTH 1920
#define RENDER_HEIGHT 1080

class ClientHandler : public CefClient,
                      public CefLifeSpanHandler,
                      public CefLoadHandler,
                      public CefRenderHandler {
    public:
    ClientHandler();
    ~ClientHandler();

    // CefClient methods
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {return this;}
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {return this;}
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE {return this;}

    // CefLifeSpanHandler methods
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    // CefLoadHandler methods
    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) OVERRIDE;

    // CefRenderHandler methods
    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) OVERRIDE;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyRects, const void *buffer, int width, int height) OVERRIDE;

    protected:
    typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
    BrowserList browser_list_;

    IMPLEMENT_REFCOUNTING(ClientHandler);
};

#endif  // LIBFRIGGA_CLIENT_HANDLER_H_