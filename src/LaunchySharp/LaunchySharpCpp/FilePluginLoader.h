#pragma once

#include "LaunchySharpCpp/IFilePluginLoader.h"
#include "Launchy/Plugin.h"
#include "LaunchySharpCpp/IPluginLoader.h"

class QString;

namespace LaunchySharpCpp {
	class PluginFactory;

	/** Loads LaunchySharp plugin from a DLL files 
		and wraps it as Launchy::Plugin 
	*/
	class FilePluginLoader: public IFilePluginLoader
	{
	public:
		FilePluginLoader(LaunchySharpCpp::IPluginLoader^ pluginLoader,
			PluginFactory& pluginFactory);

		virtual Launchy::Plugin* loadPlugin(const QString& fileName);

	private:
		gcroot< LaunchySharpCpp::IPluginLoader^ > m_pluginLoader;
		PluginFactory& m_pluginFactory;
	};
};