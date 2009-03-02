#pragma once

#include <QtGui/QWidget.h>
#include <windows.h>

namespace LaunchySharpCpp
{
	class Win32WindowWrapperWidget: public QWidget {
	public:
		Win32WindowWrapperWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);

		void setWindow(HWND windowHwnd);

		//! Does the actual work of resizing the contained window
		void refitInnerWindow();

	protected:
		//! Inherited from QWidget
		void resizeEvent(QResizeEvent* );

		HWND m_hwnd;
	};
}
