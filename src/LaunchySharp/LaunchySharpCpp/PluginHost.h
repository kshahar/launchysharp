#pragma once

namespace LaunchySharpCpp
{
	ref class PluginHost: public LaunchySharp::IPluginHost 
	{
	public:
		PluginHost();
		virtual LaunchySharp::ICatItemFactory^ catItemFactory();
	private:
		LaunchySharp::ICatItemFactory^ m_catItemFactory;
	};

}