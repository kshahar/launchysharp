#pragma once

class QWidget;

namespace LaunchySharpCpp {
	class IOptionsWidgetHandler {
	public:
		virtual ~IOptionsWidgetHandler() {}
		virtual QWidget* doDialog(QWidget* parent, System::IntPtr windowHandle) = 0;
		virtual void endDialog() = 0;
	};
}
