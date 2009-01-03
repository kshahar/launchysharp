#pragma once

#include "Launchy/plugin_interface.h"
namespace Launchy {
	class Plugin;
}

namespace LaunchySharpPlugin
{
	/** Forwards calls from PluginInterface::msg to Launchy::Plugin functions */
	class LaunchyPluginWrapper: public QObject, public PluginInterface
	{
		Q_OBJECT
		Q_INTERFACES(PluginInterface)
	public:
		LaunchyPluginWrapper(Launchy::Plugin& plugin);
		~LaunchyPluginWrapper();

		virtual int msg(int msgId, void* wParam = NULL, void* lParam = NULL);

	private:
		Launchy::Plugin& m_plugin;
	};
}