#pragma once

namespace LaunchySharpCpp
{
	interface class IPluginLoader 
	{
	public:
		LaunchySharp::IPlugin^ loadPlugin(System::String^ fileName);
	};
}