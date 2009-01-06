#pragma once

#include <memory>

namespace LaunchySharpCpp
{
	class LaunchySharpPluginWrapper;
	class LaunchySharpPluginWrapperFactory {
	public:
		LaunchySharpPluginWrapperFactory();
		~LaunchySharpPluginWrapperFactory();

		//! Ownership of memory is passed to the caller
		LaunchySharpPluginWrapper* create(LaunchySharp::IPlugin^ plugin);
	private:
		// Disable copy
		LaunchySharpPluginWrapperFactory(const LaunchySharpPluginWrapperFactory&);
		LaunchySharpPluginWrapperFactory& operator=(const LaunchySharpPluginWrapperFactory&);

		// Private implmentation in source file
		struct PrivateImpl;
		std::auto_ptr<PrivateImpl> m_pImpl;
	};

}