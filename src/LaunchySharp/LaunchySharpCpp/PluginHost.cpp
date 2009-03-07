#include "Precompiled.h"
#include "LaunchySharpCpp/PluginHost.h"
#include "LaunchySharpCpp/StringConversions.h"
#include <QtCore/QHash>

namespace LaunchySharpCpp
{

PluginHost::PluginHost(LaunchySharp::ICatItemFactory^ catItemFactory, 
			LaunchySharp::ILaunchyPaths^ launchyPaths)
: m_catItemFactory(catItemFactory),
  m_launchyPaths(launchyPaths)
{
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