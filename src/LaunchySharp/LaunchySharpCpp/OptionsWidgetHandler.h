#pragma once

#include "LaunchySharpCpp/IOptionsWidgetHandler.h"

namespace LaunchySharpCpp {
    class Win32WindowWrapperWidget;

    class OptionsWidgetHandler: public IOptionsWidgetHandler {
    public:
        OptionsWidgetHandler();
        virtual ~OptionsWidgetHandler();
        virtual QWidget* doDialog(QWidget* parent, System::IntPtr windowHandle);
        virtual void endDialog();
        
    protected:
        Win32WindowWrapperWidget* m_pWidgetWrapper;

    private:
        // Disable copy
        OptionsWidgetHandler(const OptionsWidgetHandler&);
        OptionsWidgetHandler& operator=(const OptionsWidgetHandler&);
    };

}