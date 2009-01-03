#pragma once

namespace LaunchySharp 
{
	ref class PluginLoader 
	{
	public:
		IPlugin^ loadPlugin(System::String^ fileName);

		IPlugin^ loadPluginFromTypes(cli::array<System::Type^>^ types);

		bool isValidTypeForPlugin(System::Type^ type);

		bool isLaunchyPluginType(System::Type^ type);

		IPlugin^ loadPluginFromType(System::Type^ type);
	};
}
