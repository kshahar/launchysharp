#pragma once

class QMutex;

namespace LaunchySharpPlugin
{

//! RAII-style locker for dialog functions
//! Utility class for LaunchyPluginWrapper
class DialogLocker {
public:
	DialogLocker(int msgId, QMutex& dialogMutex);
	~DialogLocker();
	bool shouldBreak() const;

private:
	int m_msgId;
	bool m_shouldBreak;
	QMutex& m_dialogMutex;
};

}