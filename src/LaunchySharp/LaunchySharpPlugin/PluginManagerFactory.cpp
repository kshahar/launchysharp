#include "Precompiled.h"
#include "LaunchySharpPlugin/PluginManagerFactory.h"
#include "LaunchySharpPlugin/PluginManager.h"
#include "LaunchySharpCpp/AssemblyResolver.h"
#include "LaunchySharpCpp/CatItemFactory.h"
#include "LaunchySharpCpp/FilePluginLoader.h"
#include "LaunchySharpCpp/LaunchyPaths.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapperFactory.h"
#include "LaunchySharpCpp/OptionsWidgetHandler.h"
#include "LaunchySharpCpp/PluginHost.h"
#include "LaunchySharpCpp/PluginLoader.h"

namespace LaunchySharpPlugin
{

// This class is needed in order to initialize before PrivateImpl is instantiated.
// Otherwise, the CLR tries to access types from Launchy#API.dll before we 
// create AssemblyResolver
struct PluginManagerFactory::Initialization
{
	msclr::auto_gcroot<LaunchySharpCpp::AssemblyResolver^> assemblyResolver;

	Initialization(const char* pluginPath):
		assemblyResolver(gcnew LaunchySharpCpp::AssemblyResolver(pluginPath))
	{
	}
};

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

PluginManagerFactory::PluginManagerFactory(QSettings* settings, const char* pluginPath)
: m_pInit(new Initialization(pluginPath)),
  m_pImpl(new PrivateImpl(settings))
{
	LOG_DEBUG("Created PluginManagerFactory");
}

PluginManagerFactory::~PluginManagerFactory()
{
}

PluginManager* PluginManagerFactory::createPluginManager()
{
	LOG_DEBUG("Creating plugin manager");
	return new PluginManager(m_pImpl->filePluginLoader);
}

}