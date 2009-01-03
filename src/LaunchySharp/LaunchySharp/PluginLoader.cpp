#include <LaunchySharp/PluginLoader.h>

using namespace System;
using namespace System::Reflection;

namespace LaunchySharp
{
IPlugin^ PluginLoader::loadPlugin(System::String^ fileName)
{
	IPlugin^ plugin = nullptr;
	try 
	{
		Assembly^ pluginAssembly = Assembly::LoadFrom(fileName);
		plugin = loadPluginFromTypes(pluginAssembly->GetTypes());
	}
	catch (Exception^ exception)
	{
		exception->ToString();
	}
	return plugin;
}

IPlugin^ PluginLoader::loadPluginFromTypes(cli::array<System::Type^>^ types)
{
	for each ( Type^ type in types )
	{
		const bool isPlugin =
			isValidTypeForPlugin(type) &&
			isLaunchyPluginType(type);
		if ( isPlugin )
		{
			return loadPluginFromType(type);
		}
	}
	return nullptr;
}

bool PluginLoader::isValidTypeForPlugin(System::Type^ type)
{
	return type->IsPublic && !type->IsAbstract;
}

bool PluginLoader::isLaunchyPluginType(System::Type^ type)
{
	return 
		type->GetInterface("LaunchySharp.IPlugin") != nullptr;
}

IPlugin^ PluginLoader::loadPluginFromType(System::Type^ type)
{
	return (IPlugin^)Activator::CreateInstance(type);
}

}