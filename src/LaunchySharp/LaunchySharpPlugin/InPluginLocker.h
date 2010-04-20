#pragma once

class QMutex;

namespace LaunchySharpPlugin
{

//! RAII-style locker for all plugin functions
//! Utility class for LaunchyPluginWrapper
class InPluginLocker {
public:
	InPluginLocker(QMutex& inPluginMutex);
	~InPluginLocker();
private:
	QMutex& m_inPluginMutex;
};

}