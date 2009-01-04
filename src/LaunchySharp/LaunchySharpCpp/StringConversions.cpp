#include "Precompiled.h"
#include "LaunchySharpCpp/StringConversions.h"
#using <mscorlib.dll>
#include <vcclr.h>

namespace LaunchySharpCpp
{
	System::String^ QStringToString(const QString& qstring)
	{
		return gcnew System::String((const wchar_t *)qstring.utf16());
	}

	QString StringToQString(System::String^ string)
	{
		pin_ptr<const wchar_t> chars = PtrToStringChars(string);
		return QString::fromUtf16((const ushort *)chars);
	}
}