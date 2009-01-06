#include "Precompiled.h"
#include "LaunchySharpCpp/LaunchyPaths.h"
#include "LaunchySharpCpp/StringConversions.h"
#include <QtCore/QCoreApplication>

namespace LaunchySharpCpp
{

LaunchyPaths::LaunchyPaths()
{
	// TODO: move out of here
	const QString applicationDirPath = 
		QCoreApplication::applicationDirPath();
	m_launchyPath = QStringToString(applicationDirPath);

	QString iconsPath = 
		applicationDirPath + 
		QDir::separator() + QString("plugins") + 
		QDir::separator() + QString("icons");
	m_iconsPath = QStringToString(iconsPath);

	m_configPath = L"";
}

System::String^ LaunchyPaths::getLaunchyPath()
{
	return m_launchyPath;
}

System::String^ LaunchyPaths::getIconsPath()
{
	return m_iconsPath;
}

System::String^ LaunchyPaths::getConfigPath()
{
	return m_configPath;
}

}