#include "Precompiled.h"
#include "LaunchySharpPlugin/PluginManager.h"
#include "LaunchySharpPlugin/LaunchyPluginWrapper.h"
#include "Launchy/Plugin.h"
#include "LaunchySharpCpp/IFilePluginLoader.h"

namespace LaunchySharpPlugin
{

PluginManager::PluginManager(LaunchySharpCpp::IFilePluginLoader& filePluginLoader)
: m_filePluginLoader(filePluginLoader)
{
}

PluginManager::~PluginManager()
{
	destroyPluginWrappers();
	destroyPlugins();
}

void PluginManager::loadPluginsFromDirectory(const QDir& pluginsDirectory)
{
	QDir pluginsDir = pluginsDirectory;
	pluginsDir.setNameFilters(QStringList("*.dll"));
	pluginsDir.setFilter(QDir::Files);
	
	foreach (QString fileName, pluginsDir.entryList()) {
		const QString absoluteFileName = 
			pluginsDir.absoluteFilePath( fileName );
		Launchy::Plugin* plugin = m_filePluginLoader.loadPlugin(absoluteFileName);

		if (plugin != NULL) {
			LOG_INFO("Adding plugin from file name %s", 
				fileName.toAscii().constData());
			addPlugin(plugin, pluginsDirectory.absolutePath());
		}
	}
}

void PluginManager::sendPluginsToLaunchy(QList<PluginInfo>* additionalPlugins)
{
	PluginManager::PluginInfoHash::const_iterator itr = 
		m_pluginWrappers.constBegin();
	PluginManager::PluginInfoHash::const_iterator itrEnd = 
		m_pluginWrappers.constEnd();

	for ( ; itr != itrEnd; ++itr ) {
		additionalPlugins->push_back(itr.value());
	}
}

void PluginManager::unloadPlugin(uint id)
{
}

void PluginManager::addPlugin(Launchy::Plugin* pPlugin, QString path)
{
	PluginInterface* pPluginWrapper = 
		new LaunchyPluginWrapper(*pPlugin);

	// Create PluginInfo so we can tell launchy about the plugin
	PluginInfo launchyPluginInfo;

	pPluginWrapper->msg(MSG_INIT, NULL, NULL);
	pPluginWrapper->msg(MSG_GET_ID, &launchyPluginInfo.id, NULL);
	pPluginWrapper->msg(MSG_GET_NAME, &launchyPluginInfo.name, NULL);
	pPluginWrapper->msg(MSG_PATH, &path, NULL);

	launchyPluginInfo.path = "";
	launchyPluginInfo.obj = pPluginWrapper;

	LOG_INFO("Plugin info (id, name): (%i, %s)",
		launchyPluginInfo.id,
		launchyPluginInfo.name.toLatin1().constData()
	);
	
	m_pluginWrappers[launchyPluginInfo.id] = launchyPluginInfo;
	m_plugins.append(pPlugin);
}

void PluginManager::destroyPlugins()
{
	foreach(Launchy::Plugin* pPlugin, m_plugins) {
		delete pPlugin;
	}
	m_plugins.clear();
}

void PluginManager::destroyPluginWrappers()
{
	PluginManager::PluginInfoHash::const_iterator itr = 
		m_pluginWrappers.constBegin();
	PluginManager::PluginInfoHash::const_iterator itrEnd = 
		m_pluginWrappers.constEnd();
		
	for ( ; itr != itrEnd; ++itr ) {
		delete itr.value().obj;
	}

	m_pluginWrappers.clear();
}

}