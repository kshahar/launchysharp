#include "Precompiled.h"
#include "LaunchySharpCpp/PluginHost.h"
#include "LaunchySharpCpp/CatItemFactory.h"
#include "LaunchySharpCpp/LaunchyPaths.h"
#include "LaunchySharpCpp/StringConversions.h"
#include <QtCore/QHash>

namespace LaunchySharpCpp
{

PluginHost::PluginHost()
{
	m_catItemFactory = gcnew CatItemFactory();
	m_launchyPaths = gcnew LaunchyPaths();
}

LaunchySharp::ICatItemFactory^ PluginHost::catItemFactory()
{
	return m_catItemFactory;
}

LaunchySharp::ILaunchyPaths^ PluginHost::launchyPaths()
{
	return m_launchyPaths;
}

unsigned int PluginHost::hash(System::String^ str)
{
	QString qstr = StringToQString(str);
	return qHash(qstr);
}

}