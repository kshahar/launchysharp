#pragma once

class QSettings;

namespace LaunchySharpPlugin
{
	class PluginManager;

	class PluginManagerFactory
	{
	public:
		PluginManagerFactory(QSettings* settings);
		~PluginManagerFactory();

		//! Ownership of memory is passed to the caller
		virtual PluginManager* createPluginManager();
	private:
		// Disable copy
		PluginManagerFactory(const PluginManagerFactory&);
		PluginManagerFactory& operator=(const PluginManagerFactory&);

		// Private implmentation in source file
		struct PrivateImpl;
		std::auto_ptr<PrivateImpl> m_pImpl;
	};
}
