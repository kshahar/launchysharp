#include "Precompiled.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapperFactory.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapper.h"
#include "LaunchySharpCpp/PluginHost.h"
#include "LaunchySharpCpp/CatItemConverter.h"
#include "LaunchySharpCpp/InputDataFactory.h"
#include "LaunchySharpCpp/InputDataListConverter.h"
#include <gcroot.h>

namespace LaunchySharpCpp
{

struct LaunchySharpPluginWrapperFactory::PrivateImpl
{
	gcroot<LaunchySharp::IPluginHost^> pluginHost;
	LaunchySharpCpp::CatItemConverter catItemConverter;
	LaunchySharpCpp::InputDataFactory inputDataFactory;
	LaunchySharpCpp::InputDataListConverter inputDataListConverter;
	LaunchySharpCpp::IOptionsWidgetHandler& optionsWidgetHandler;

	PrivateImpl(
		LaunchySharp::IPluginHost^ pluginHost_,
		LaunchySharpCpp::IOptionsWidgetHandler& optionsWidgetHandler_):
		inputDataListConverter(inputDataFactory),
		pluginHost(pluginHost_),
		optionsWidgetHandler(optionsWidgetHandler_)
	{
	}
};

LaunchySharpPluginWrapperFactory::LaunchySharpPluginWrapperFactory(
	LaunchySharp::IPluginHost^ pluginHost,
	LaunchySharpCpp::IOptionsWidgetHandler& optionsWidgetHandler)
: m_pImpl(new PrivateImpl(pluginHost, optionsWidgetHandler))
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