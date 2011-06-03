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
	QString path;

	PrivateImpl(QSettings* settings, const char* pluginPath):
	pluginManagerFactory(settings, pluginPath),
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
	else if (msgId == MSG_PATH) {
		setPath((QString*) wParam);
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

	LOG_INFO("Initializing");
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
	LOG_INFO("Beginning to load plugins");

	if (!m_pImpl->path.isEmpty()) { 
		m_pImpl->pPluginManager->loadPluginsFromDirectory(m_pImpl->path);
	}

	const QDir pluginsDir = QCoreApplication::applicationDirPath() +
			QDir::separator() + 
			"plugins";

	if (pluginsDir != m_pImpl->path) {
		// try also standard plugin directory, if it's not the one we've started in
		m_pImpl->pPluginManager->loadPluginsFromDirectory(pluginsDir);
	}
	
	m_pImpl->pPluginManager->sendPluginsToLaunchy(additionalPlugins);
}

void Plugin::unloadPlugin(uint id)
{
	LOG_INFO("Unloading plugin %d", id);
	m_pImpl->pPluginManager->unloadPlugin(id);
}

void Plugin::setPath(QString* pPluginPath)
{
	if (m_pImpl.get() != NULL) {
		return;
	}

	const QByteArray pathByteArray = pPluginPath->toLatin1();
	const char* path = pathByteArray.constData();
	LOG_INFO("Plugin path is %s", path);

	m_pImpl.reset(new PrivateImpl(*settings, path));
	m_pImpl->path = *pPluginPath;
}

}

Q_EXPORT_PLUGIN2(LaunchySharpPlugin, LaunchySharpPlugin::Plugin) 
