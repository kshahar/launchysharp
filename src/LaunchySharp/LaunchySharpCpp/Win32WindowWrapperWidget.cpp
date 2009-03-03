#include "Precompiled.h"
#include "LaunchySharpCpp/Win32WindowWrapperWidget.h"

namespace LaunchySharpCpp
{

Win32WindowWrapperWidget::Win32WindowWrapperWidget( QWidget* parent /*= 0*/, 
	 Qt::WindowFlags f /*= 0*/ ) 
: QWidget(parent, f), 
  m_hwnd(0),
  m_oldParent(0)
{

}

void Win32WindowWrapperWidget::setWindow( HWND windowHwnd )
{
	m_hwnd = windowHwnd;
	m_oldParent = ::GetParent(m_hwnd);
	::SetParent( m_hwnd, winId() );
	//::SetWindowLong( windowHwnd, GWL_STYLE, WS_VISIBLE);

	refitInnerWindow();
}

void Win32WindowWrapperWidget::unsetWindow()
{
	::SetParent(m_hwnd, m_oldParent);
	hideWindow(m_hwnd);
}

void Win32WindowWrapperWidget::refitInnerWindow()
{
	if (m_hwnd == 0) {
		return;
	}

	hideWindow(m_hwnd);

	const QSize& size = this->size();
	const BOOL moveResult = 
		::MoveWindow( m_hwnd, 0, 0, size.width(), size.height(), true );

	showWindow(m_hwnd);
}

void Win32WindowWrapperWidget::resizeEvent( QResizeEvent* )
{
	refitInnerWindow();
}


void Win32WindowWrapperWidget::showWindow(HWND hWnd)
{
	::ShowWindow(m_hwnd, SW_SHOW);
}

void Win32WindowWrapperWidget::hideWindow(HWND hWnd)
{
	::ShowWindow(m_hwnd, SW_HIDE);
}

}