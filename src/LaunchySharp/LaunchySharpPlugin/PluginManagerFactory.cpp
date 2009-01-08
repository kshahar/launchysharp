#include "Precompiled.h"
#include "LaunchySharpPlugin/PluginManagerFactory.h"
#include "LaunchySharpPlugin/PluginManager.h"
#include "LaunchySharpCpp/FilePluginLoader.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapperFactory.h"
#include "LaunchySharpCpp/PluginLoader.h"

namespace LaunchySharpPlugin
{

struct PluginManagerFactory::PrivateImpl
{
	LaunchySharpCpp::LaunchySharpPluginWrapperFactory pluginFactory;
	LaunchySharpCpp::FilePluginLoader filePluginLoader;

	PrivateImpl():
	filePluginLoader(gcnew LaunchySharpCpp::PluginLoader, pluginFactory)
	{
	}
};

PluginManagerFactory::PluginManagerFactory()
: m_pImpl(new PrivateImpl)
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