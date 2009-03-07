#pragma once

#include <memory>
#include "LaunchySharpCpp/PluginFactory.h"

namespace Launchy {
	class Plugin;
}

namespace LaunchySharpCpp
{
	class IOptionsWidgetHandler;

	class LaunchySharpPluginWrapperFactory: public PluginFactory {
	public:
		LaunchySharpPluginWrapperFactory(
			LaunchySharp::IPluginHost^ pluginHost,
			LaunchySharpCpp::IOptionsWidgetHandler& optionsWidgetHandler);
		~LaunchySharpPluginWrapperFactory();

		//! Ownership of memory is passed to the caller
		virtual Launchy::Plugin* create(LaunchySharp::IPlugin^ plugin);
	private:
		// Disable copy
		LaunchySharpPluginWrapperFactory(const LaunchySharpPluginWrapperFactory&);
		LaunchySharpPluginWrapperFactory& operator=(const LaunchySharpPluginWrapperFactory&);

		// Private implmentation in source file
		struct PrivateImpl;
		std::auto_ptr<PrivateImpl> m_pImpl;
	};

}