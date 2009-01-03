#pragma once

#include <QtCore/QString>

namespace LaunchySharpCpp
{
	System::String^ QStringToString(const QString& qstring);

	QString StringToQString(System::String^ string);
}