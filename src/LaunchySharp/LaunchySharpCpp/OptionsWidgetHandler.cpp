#include "Precompiled.h"
#include "LaunchySharpCpp/OptionsWidgetHandler.h"
#include "LaunchySharpCpp/Win32WindowWrapperWidget.h"

namespace LaunchySharpCpp {

OptionsWidgetHandler::OptionsWidgetHandler()
: m_pWidgetWrapper(NULL)
{
}

OptionsWidgetHandler::~OptionsWidgetHandler()
{
    endDialog();
}

QWidget* OptionsWidgetHandler::doDialog(QWidget* parent, System::IntPtr windowHandle)
{
    if (m_pWidgetWrapper) {
        return m_pWidgetWrapper;
    }
    
	if (windowHandle.ToInt32() == 0) {
		return NULL;
	}
	HWND hWnd = reinterpret_cast<HWND>( windowHandle.ToPointer() );

    m_pWidgetWrapper = new Win32WindowWrapperWidget(parent);
    m_pWidgetWrapper->setWindow(hWnd);
	return m_pWidgetWrapper;
}

void OptionsWidgetHandler::endDialog()
{
    if (m_pWidgetWrapper) {
        m_pWidgetWrapper->unsetWindow();
        delete m_pWidgetWrapper;
        m_pWidgetWrapper = NULL;
    }
}

}
