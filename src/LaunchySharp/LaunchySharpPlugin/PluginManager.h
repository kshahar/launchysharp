#pragma once

#include "Launchy/plugin_interface.h"
#include "Launchy/plugin_info.h"
#include <QtCore/QHash>
#include <QtCore/QList>

namespace Launchy {
	class Plugin;
}
namespace LaunchySharpCpp {
	class IFilePluginLoader;
}

namespace LaunchySharpPlugin
{
	class PluginManager 
	{
	public:
		PluginManager(LaunchySharpCpp::IFilePluginLoader& filePluginLoader);
		~PluginManager();

		//! Should be called once, on startup
		void loadPluginsFromDirectory(
			const QDir& pluginsDirectory);
		
		// Response to the MSG_LOAD_PLUGINS message
		void sendPluginsToLaunchy(
			QList<PluginInfo>* additionalPlugins);

		//! Response to the MSG_UNLOAD_PLUGIN message
		void PluginManager::unloadPlugin(uint id);

	private:
		void addPlugin(Launchy::Plugin* pPlugin, QString path);

		void destroyPlugins();

		void destroyPluginWrappers();

		typedef QHash<uint, PluginInfo> PluginInfoHash;
		LaunchySharpCpp::IFilePluginLoader& m_filePluginLoader;
		QList<Launchy::Plugin*> m_plugins;
		PluginInfoHash m_pluginWrappers;
	};
}