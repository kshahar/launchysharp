#pragma once

namespace LaunchySharpCpp
{
	ref class LaunchyPaths: public LaunchySharp::ILaunchyPaths 
	{
	public:
		LaunchyPaths(QSettings* settings);

		/// Usually C:\Program Files\Launchy
		virtual System::String^ getLaunchyPath();
		
		/// Usually C:\Program Files\Launchy\plugins\icons
		virtual System::String^ getIconsPath();
		
		/// Usually %AppData%\Launchy\ 
		virtual System::String^ getConfigPath();

	private:
		System::String^ m_launchyPath;
		System::String^ m_iconsPath;
		System::String^ m_configPath;
	};

}