#pragma once

#using <mscorlib.dll>
#include <vcclr.h>
#include <msclr/auto_gcroot.h>

#include <windows.h>
#include <shlobj.h>

#pragma warning( push )
#pragma warning( disable : 4561 ) // '__fastcall' incompatible with the '/clr' option: converting to '__stdcall'
#pragma warning( disable : 4793 ) // 'vararg' : causes native code generation for function *

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QBitArray>
#include <QtCore/QHash>
#include <QtCore/QDir>
#include <QtCore/QList>
#include <QtCore/QMutex>
#include <QtCore/QSet>
#include <QtCore/QSettings>
#include <QtCore/QtPlugin>
#include <QtCore/QPluginLoader>
#include <QtGui/QIcon>
#include <QtGui/QWidget>

#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable : 4996 ) // '*' was declared deprecated

#include <cstdio>
#include <cstdlib>
#include "launchysharp_ezlogger_adapter.h"

#pragma warning( pop )
