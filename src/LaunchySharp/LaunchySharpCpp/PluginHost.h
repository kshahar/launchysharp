#pragma once

namespace LaunchySharpCpp
{
	ref class PluginHost: public LaunchySharp::IPluginHost 
	{
	public:
		PluginHost(LaunchySharp::ICatItemFactory^ catItemFactory, 
			LaunchySharp::ILaunchyPaths^ launchyPaths);

		virtual LaunchySharp::ICatItemFactory^ catItemFactory();

		virtual LaunchySharp::ILaunchyPaths^ launchyPaths();

		virtual unsigned int hash(System::String^ str);
	private:
		LaunchySharp::ICatItemFactory^ m_catItemFactory;
		LaunchySharp::ILaunchyPaths^ m_launchyPaths;
	};

}