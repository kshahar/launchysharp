#include "Precompiled.h"
#include "LaunchySharpPlugin/Plugin.h"
#include <QTimerEvent>
#include <QEvent>
#include <QChildEvent>
#include <QtPlugin>

#include <LaunchySharpCpp/TestPlugin.h>
#include <LaunchySharpCpp/LaunchySharpPluginWrapper.h>
#include <LaunchySharpPlugin/LaunchyPluginWrapper.h>

namespace LaunchySharpPlugin
{

Plugin* g_pluginInstance = NULL;
const char* CONFIG_pluginName = "Launchy#";
unsigned int CONFIG_pluginHash = qHash(CONFIG_pluginName);

PluginInfo pluginInfo;
LaunchySharpCpp::LaunchySharpPluginWrapper* sharpWrapper;
LaunchySharpPlugin::LaunchyPluginWrapper* launchyWrapper;


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
		//m_pImpl->unloadPlugin((uint)wParam);
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

	/*sharpWrapper = new LaunchySharpCpp::LaunchySharpPluginWrapper(
		gcnew LaunchySharpCpp::TestPlugin());
	launchyWrapper = new LaunchySharpPlugin::LaunchyPluginWrapper(
		*sharpWrapper);

	sharpWrapper->getID(&pluginInfo.id);
	sharpWrapper->getName(&pluginInfo.name);
	pluginInfo.path = "";
	pluginInfo.obj = launchyWrapper;*/
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
	additionalPlugins->append(pluginInfo);
}

}

Q_EXPORT_PLUGIN2(LaunchySharpPlugin, LaunchySharpPlugin::Plugin) 