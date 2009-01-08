#include "Precompiled.h"
#include "LaunchySharpCpp/PluginLoader.h"

using namespace System;
using namespace System::Reflection;

namespace LaunchySharpCpp
{

LaunchySharp::IPlugin^ PluginLoader::loadPlugin(System::String^ fileName)
{
	LaunchySharp::IPlugin^ plugin = nullptr;
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

LaunchySharp::IPlugin^ PluginLoader::loadPluginFromTypes(cli::array<System::Type^>^ types)
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

LaunchySharp::IPlugin^ PluginLoader::loadPluginFromType(System::Type^ type)
{
	return (LaunchySharp::IPlugin^)Activator::CreateInstance(type);
}

}