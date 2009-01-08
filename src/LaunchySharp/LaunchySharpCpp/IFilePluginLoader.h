#pragma once

namespace Launchy {
	class Plugin;
}
class QString;

namespace LaunchySharpCpp {
	/** Loads LaunchySharp plugin from a DLL files 
		and wraps it as Launchy::Plugin 
	*/
	class IFilePluginLoader 
	{
	public:
		virtual Launchy::Plugin* loadPlugin(const QString& fileName) = 0;
	};
};
