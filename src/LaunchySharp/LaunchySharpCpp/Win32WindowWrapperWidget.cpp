#include "Precompiled.h"
#include "LaunchySharpCpp/Win32WindowWrapperWidget.h"

namespace LaunchySharpCpp
{

Win32WindowWrapperWidget::Win32WindowWrapperWidget( QWidget* parent /*= 0*/, 
	 Qt::WindowFlags f /*= 0*/ ) 
: QWidget(parent, f), 
  m_hwnd(0)
{

}

void Win32WindowWrapperWidget::setWindow( HWND windowHwnd )
{
	m_hwnd = windowHwnd;
	::SetParent( windowHwnd, winId() );
	//::SetWindowLong( windowHwnd, GWL_STYLE, WS_VISIBLE);

	refitInnerWindow();
}

void Win32WindowWrapperWidget::refitInnerWindow()
{
	if (m_hwnd == 0) {
		return;
	}

	::ShowWindow(m_hwnd, SW_HIDE);

	//::SetParent(m_hwnd, 0);
	const QSize& size = this->size();
	const BOOL moveResult = 
		::MoveWindow( m_hwnd, 0, 0, size.width(), size.height(), true );
	//::SetParent(m_hwnd, winId() );

	::ShowWindow(m_hwnd, SW_SHOW);
}

void Win32WindowWrapperWidget::resizeEvent( QResizeEvent* )
{
	refitInnerWindow();
}

}