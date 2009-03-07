#include "Precompiled.h"
#include "LaunchySharpPlugin/Plugin.h"
#include <QtCore/QCoreApplication>
#include <QtPlugin>

#include "LaunchySharpPlugin/PluginManager.h"
#include "LaunchySharpPlugin/PluginManagerFactory.h"

namespace LaunchySharpPlugin
{

static Plugin* g_pluginInstance = NULL;
const char* CONFIG_pluginName = "Launchy#";
unsigned int CONFIG_pluginHash = qHash(CONFIG_pluginName);

struct Plugin::PrivateImpl
{
	PluginManagerFactory pluginManagerFactory;
	std::auto_ptr<PluginManager> pPluginManager;

	PrivateImpl(QSettings* settings):
	pluginManagerFactory(settings),
	pPluginManager(pluginManagerFactory.createPluginManager())
	{
	}
};

Plugin::Plugin()
{

}

Plugin::~Plugin()
{
}

int Plugin::msg(int msgId, void* wParam, void* lParam)
{
	if (msgId == MSG_INIT) {
		init();
	}
	else if (msgId == MSG_GET_ID) {
		getID((uint*) wParam);
	}
	else if (msgId == MSG_GET_NAME) {
		getName((QString*) wParam);
	}
	else if (msgId == MSG_LOAD_PLUGINS) {
		loadPlugins((QList<PluginInfo>*)wParam);
	}
	else if (msgId == MSG_UNLOAD_PLUGIN) {
		unloadPlugin((uint)wParam);
	}
	else if (msgId == MSG_HAS_DIALOG) {
		// This is the only case we return false
		return false;
	}
	
	// Message was handled so we return true
	return true;	
}

void Plugin::init()
{
	if (g_pluginInstance != NULL) {
		return;
	}
	g_pluginInstance = this;

	m_pImpl.reset(new PrivateImpl(*settings));

	const QDir pluginsDir = 
		QCoreApplication::applicationDirPath() + 
		QDir::separator() +
		"plugins";
	m_pImpl->pPluginManager->loadPluginsFromDirectory(pluginsDir);
}

void Plugin::getID(uint* pId)
{
	*pId = CONFIG_pluginHash;
}

void Plugin::getName(QString* pName)
{
	*pName = CONFIG_pluginName;
}

void Plugin::loadPlugins(QList<PluginInfo>* additionalPlugins)
{
	m_pImpl->pPluginManager->sendPluginsToLaunchy(additionalPlugins);
}

void Plugin::unloadPlugin(uint id)
{
	m_pImpl->pPluginManager->unloadPlugin(id);
}

}

Q_EXPORT_PLUGIN2(LaunchySharpPlugin, LaunchySharpPlugin::Plugin) 