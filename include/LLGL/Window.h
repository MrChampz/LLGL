/*
 * Window.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __LLGL_WINDOW_H__
#define __LLGL_WINDOW_H__


#include <string>
#include <memory>
#include <vector>
#include <LLGL/Export.h>
#include <LLGL/Key.h>
#include <LLGL/Types.h>


namespace LLGL
{


//! Window descriptor structure.
struct WindowDescriptor
{
    std::wstring    title;
    Point           position;                       //!< Window position (relative to the client area).
    Size            size;                           //!< Client area size.

    bool            visible             = false;
    bool            borderless          = false;
    bool            resizable           = false;
    bool            acceptDropFiles     = false;
    bool            preventForPowerSafe = false;
    bool            centered            = false;

    void*           parentWindow        = nullptr;
};


// Interface for a Window class (also named Canvas)
class LLGL_EXPORT Window
{

    public:

        // Interface for all window listeners
        class LLGL_EXPORT EventListener
        {

            public:

                virtual ~EventListener();

            protected:

                friend class Window;

                virtual void OnReset(Window& sender);

                virtual void OnKeyDown(Window& sender, Key keyCode);
                virtual void OnKeyUp(Window& sender, Key keyCode);
                
                virtual void OnChar(Window& sender, wchar_t chr);

                virtual void OnWheelMotion(Window& sender, int motion);

                virtual void OnLocalMotion(Window& sender, const Point& position);
                virtual void OnGlobalMotion(Window& sender, const Point& motion);

                //! Returns true if the specified window can quit, i.e. "ProcessEvents" returns false from now on.
                virtual bool OnQuit(Window& sender);

        };

        /* --- Common --- */

        virtual ~Window();

        static std::unique_ptr<Window> Create(const WindowDescriptor& desc);

        virtual void SetPosition(const Point& position) = 0;
        virtual Point GetPosition() const = 0;

        virtual void SetSize(const Size& size, bool useClientArea = true) = 0;
        virtual Size GetSize(bool useClientArea = true) const = 0;

        virtual void SetTitle(const std::wstring& title) = 0;
        virtual std::wstring GetTitle() const = 0;

        virtual void Show(bool show = true) = 0;
        virtual bool IsShown() const = 0;

        /**
        Returns the native window handle.
        For Windows, cast this to 'const HWND*'
        For MacOS, cast this to 'const NSWindow**'
        For Linux, cast this to 'const ::Window*'
        */
        virtual const void* GetNativeHandle() const = 0;

        bool ProcessEvents();

        /* --- Event handling --- */

        void AddEventListener(const std::shared_ptr<EventListener>& eventListener);
        void RemoveEventListener(const EventListener* eventListener);

        void PostKeyDown(Key keyCode);
        void PostKeyUp(Key keyCode);
        
        void PostChar(wchar_t chr);
        
        void PostWheelMotion(int motion);
        
        void PostLocalMotion(const Point& position);
        void PostGlobalMotion(const Point& motion);

        /**
        \brief Posts the 'OnQuit' event to all event listeners.
        \remarks If at least one event listener returns false within the "OnQuit" callback, the window will not quit.
        If all event listener return true within the "OnQuit" callback, "ProcessEvents" will returns false from now on.
        */
        void PostQuit();

    protected:

        virtual void ProcessSystemEvents() = 0;

    private:

        std::vector<std::shared_ptr<EventListener>> eventListeners_;

        bool quit_ = false;

};


} // /namespace LLGL


#endif



// ================================================================================