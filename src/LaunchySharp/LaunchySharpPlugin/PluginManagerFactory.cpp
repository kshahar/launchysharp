#include "Precompiled.h"
#include "LaunchySharpPlugin/PluginManagerFactory.h"
#include "LaunchySharpPlugin/PluginManager.h"
#include "LaunchySharpCpp/CatItemFactory.h"
#include "LaunchySharpCpp/FilePluginLoader.h"
#include "LaunchySharpCpp/LaunchyPaths.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapperFactory.h"
#include "LaunchySharpCpp/PluginHost.h"
#include "LaunchySharpCpp/PluginLoader.h"

namespace LaunchySharpPlugin
{

struct PluginManagerFactory::PrivateImpl
{
	gcroot<LaunchySharp::ICatItemFactory^> catItemFactory;
	gcroot<LaunchySharp::ILaunchyPaths^> launchyPaths;
	gcroot<LaunchySharp::IPluginHost^> pluginHost;
	LaunchySharpCpp::LaunchySharpPluginWrapperFactory pluginFactory;
	LaunchySharpCpp::FilePluginLoader filePluginLoader;

	PrivateImpl(QSettings* settings):
	catItemFactory(gcnew LaunchySharpCpp::CatItemFactory),
	launchyPaths(gcnew LaunchySharpCpp::LaunchyPaths(settings->fileName())),
	pluginHost(gcnew LaunchySharpCpp::PluginHost(catItemFactory, launchyPaths)),
	pluginFactory(pluginHost),
	filePluginLoader(gcnew LaunchySharpCpp::PluginLoader, pluginFactory)
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