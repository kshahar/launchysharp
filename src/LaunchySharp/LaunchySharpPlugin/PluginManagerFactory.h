#pragma once

class QSettings;

namespace LaunchySharpPlugin
{
	class PluginManager;

	class PluginManagerFactory
	{
	public:
		PluginManagerFactory(QSettings* settings, const char* pluginPath);
		~PluginManagerFactory();

		//! Ownership of memory is passed to the caller
		virtual PluginManager* createPluginManager();
	private:
		// Disable copy
		PluginManagerFactory(const PluginManagerFactory&);
		PluginManagerFactory& operator=(const PluginManagerFactory&);

		// Some way of doing initialization before PrivateImpl is constructed
		struct Initialization;
		std::auto_ptr<Initialization> m_pInit;

		// Private implementation in source file
		struct PrivateImpl;
		std::auto_ptr<PrivateImpl> m_pImpl;
	};
}
