#if 0
#include "Launchy/plugin_interface.h"
#include "LaunchySharp/PluginLoader.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapper.h"


#include <memory>
int main(array<System::String ^> ^args)
{
	LaunchySharp::PluginLoader^ pluginLoader = 
		gcnew LaunchySharp::PluginLoader();
	LaunchySharp::IPlugin^ sharpPlugin = 
		pluginLoader->loadPlugin(L"TestPlugin.dll");

	{
	Launchy::Plugin* plugin =
		new LaunchySharpCpp::LaunchySharpPluginWrapper(sharpPlugin);
	std::auto_ptr<Launchy::Plugin> pluginGuard(plugin);
	QString name;
	plugin->getName( &name );
	printf("%s\n", (const char*)name.toUtf8());
	}

    return 0;
}
#endif