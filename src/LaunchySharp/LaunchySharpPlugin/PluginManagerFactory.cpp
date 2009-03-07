#include "Precompiled.h"
#include "LaunchySharpPlugin/PluginManagerFactory.h"
#include "LaunchySharpPlugin/PluginManager.h"
#include "LaunchySharpCpp/CatItemFactory.h"
#include "LaunchySharpCpp/FilePluginLoader.h"
#include "LaunchySharpCpp/LaunchyPaths.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapperFactory.h"
#include "LaunchySharpCpp/OptionsWidgetHandler.h"
#include "LaunchySharpCpp/PluginHost.h"
#include "LaunchySharpCpp/PluginLoader.h"

namespace LaunchySharpPlugin
{

struct PluginManagerFactory::PrivateImpl
{
	msclr::auto_gcroot<LaunchySharp::ICatItemFactory^> catItemFactory;
	msclr::auto_gcroot<LaunchySharp::ILaunchyPaths^> launchyPaths;
	msclr::auto_gcroot<LaunchySharp::IPluginHost^> pluginHost;
	LaunchySharpCpp::OptionsWidgetHandler optionsWidgetHandler;
	LaunchySharpCpp::LaunchySharpPluginWrapperFactory pluginFactory;
	msclr::auto_gcroot<LaunchySharpCpp::IPluginLoader^> m_pluginLoader;
	LaunchySharpCpp::FilePluginLoader filePluginLoader;

	PrivateImpl(QSettings* settings):
	catItemFactory(gcnew LaunchySharpCpp::CatItemFactory),
	launchyPaths(gcnew LaunchySharpCpp::LaunchyPaths(settings)),
	pluginHost(gcnew LaunchySharpCpp::PluginHost(catItemFactory.get(), launchyPaths.get())),
	pluginFactory(pluginHost.get(), optionsWidgetHandler),
	m_pluginLoader(gcnew LaunchySharpCpp::PluginLoader),
	filePluginLoader(m_pluginLoader.get(), pluginFactory)
	{
	}
};

PluginManagerFactory::PluginManagerFactory(QSettings* settings)
: m_pImpl(new PrivateImpl(settings))
{
}

PluginManagerFactory::~PluginManagerFactory()
{
}

PluginManager* PluginManagerFactory::createPluginManager()
{
	return new PluginManager(m_pImpl->filePluginLoader);
}

}