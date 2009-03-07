#pragma once

#pragma once

#include "LaunchySharpCpp/IOptionsWidgetHandler.h"

namespace LaunchySharpCpp 
{
namespace testing
{
	class FakeOptionsWidgetHandler: public LaunchySharpCpp::IOptionsWidgetHandler {
	public:
		virtual QWidget* doDialog(QWidget* parent, System::IntPtr windowHandle)
		{
			return 0;
		}
		virtual void endDialog()
		{
		}
	};
}
}