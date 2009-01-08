#pragma once

#include "LaunchySharpCpp/IPluginLoader.h"

namespace LaunchySharpCpp 
{
	ref class PluginLoader: public IPluginLoader
	{
	public:
		virtual LaunchySharp::IPlugin^ loadPlugin(System::String^ fileName);

		LaunchySharp::IPlugin^ loadPluginFromTypes(cli::array<System::Type^>^ types);

		bool isValidTypeForPlugin(System::Type^ type);

		bool isLaunchyPluginType(System::Type^ type);

		LaunchySharp::IPlugin^ loadPluginFromType(System::Type^ type);
	};
}
