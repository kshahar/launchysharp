#include "Precompiled.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapperFactory.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapper.h"
#include "LaunchySharpCpp/PluginHost.h"
#include "LaunchySharpCpp/CatItemConverter.h"
#include "LaunchySharpCpp/InputDataFactory.h"
#include "LaunchySharpCpp/InputDataListConverter.h"
#include "LaunchySharpCpp/OptionsWidgetHandler.h"
#include <gcroot.h>

namespace LaunchySharpCpp
{

struct LaunchySharpPluginWrapperFactory::PrivateImpl
{
	gcroot<LaunchySharp::IPluginHost^> pluginHost;
	LaunchySharpCpp::CatItemConverter catItemConverter;
	LaunchySharpCpp::InputDataFactory inputDataFactory;
	LaunchySharpCpp::InputDataListConverter inputDataListConverter;
	LaunchySharpCpp::OptionsWidgetHandler optionsWidgetHandler;

	PrivateImpl():
		inputDataListConverter(inputDataFactory)
	{
		pluginHost = gcnew LaunchySharpCpp::PluginHost();
	}
};

LaunchySharpPluginWrapperFactory::LaunchySharpPluginWrapperFactory()
: m_pImpl(new PrivateImpl)
{
}

LaunchySharpPluginWrapperFactory::~LaunchySharpPluginWrapperFactory()
{
}

Launchy::Plugin* LaunchySharpPluginWrapperFactory::create(
	LaunchySharp::IPlugin^ plugin)
{
	return new LaunchySharpPluginWrapper(plugin,
		m_pImpl->pluginHost, 
		m_pImpl->catItemConverter,
		m_pImpl->inputDataListConverter,
		m_pImpl->optionsWidgetHandler
	);
}

}