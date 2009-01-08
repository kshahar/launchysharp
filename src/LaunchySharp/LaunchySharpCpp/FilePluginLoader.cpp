#include "Precompiled.h"
#include "LaunchySharpCpp/FilePluginLoader.h"
#include "LaunchySharpCpp/PluginFactory.h"
#include "LaunchySharpCpp/StringConversions.h"
#include <QtCore/QDir>

namespace LaunchySharpCpp
{

FilePluginLoader::FilePluginLoader(
	LaunchySharpCpp::IPluginLoader^ pluginLoader,
	PluginFactory& pluginFactory)
: m_pluginLoader(pluginLoader),
  m_pluginFactory(pluginFactory)
{
}

Launchy::Plugin* FilePluginLoader::loadPlugin(const QString& fileName)
{
	System::String^ clrFileName = QStringToString(fileName);
	LaunchySharp::IPlugin^ sharpPlugin = 
		m_pluginLoader->loadPlugin( clrFileName );

	if (sharpPlugin != nullptr) {
		Launchy::Plugin* launchyPlugin = 
			m_pluginFactory.create(sharpPlugin);
		return launchyPlugin;
	}
	else {	
		return NULL;
	}
}

}