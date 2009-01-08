#pragma once

#include <memory>

namespace Launchy {
	class Plugin;
}

namespace LaunchySharpCpp
{
	class PluginFactory 
	{
	public:
		//! Ownership of memory is passed to the caller
		virtual Launchy::Plugin* create(LaunchySharp::IPlugin^ plugin) = 0;
	};
}