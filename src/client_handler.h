#ifndef LIBFRIGGA_CLIENT_HANDLER_H_
#define LIBFRIGGA_CLIENT_HANDLER_H_


#include "include/cef_render_process_handler.h"
#include "include/cef_client.h"
#include "include/cef_v8.h"
#include "include/cef_browser.h"

#include <list>

#define RENDER_WIDTH 1920
#define RENDER_HEIGHT 1080

class ClientHandler : public CefClient, //gives access to root of diff handlers that can be attached
                      public CefLifeSpanHandler, //events having to do with lifespan of "window"
                      public CefLoadHandler, //events when the physical window frames load
                      public CefRenderHandler { //deals with rendering (need it for windowless state)
    public:
    ClientHandler();
    ~ClientHandler();

    CefRefPtr<CefBrowser> GetBrowser()
    {
        return m_Browser;
    }

    CefWindowHandle GetBrowserHwnd()
    {
        return m_BrowserHwnd;
    }

    // CefClient methods
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {return this;}
    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {return this;}
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE {return this;}

    // CefLifeSpanHandler methods
    //What happens with the actual windows that are opened
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

    // CefLoadHandler methods
    //when loading ends for a page (eg: getting html for a page)
    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) OVERRIDE;

    // CefRenderHandler methods
    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) OVERRIDE;
    virtual void OnPaint(CefRefPtr<CefBrowser> browser, CefRenderHandler::PaintElementType type, const CefRenderHandler::RectList &dirtyRects, const void *buffer, int width, int height) OVERRIDE;

    protected:
    typedef std::list<CefRefPtr<CefBrowser>> BrowserList; //List of handlers to gives access to all diff components of a web page
    BrowserList browser_list_;
    // The child browser window
    CefRefPtr<CefBrowser> m_Browser;

    // The child browser window handle
    CefWindowHandle m_BrowserHwnd;

    IMPLEMENT_REFCOUNTING(ClientHandler);
};

#endif  // LIBFRIGGA_CLIENT_HANDLER_H_
