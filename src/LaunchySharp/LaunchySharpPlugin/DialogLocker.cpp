#include "Precompiled.h"
#include "LaunchySharpPlugin/DialogLocker.h"

#include <QtCore/QMutex>
#include "Launchy/plugin_interface.h"

namespace LaunchySharpPlugin
{

DialogLocker::DialogLocker(int msgId, QMutex& dialogMutex)
: m_dialogMutex(dialogMutex), 
  m_msgId(msgId), 
  m_shouldBreak(false)
{
	// We can't allow plugin functions to be called when doDialog was called
	// and endDialog not called yet, since it is dangerous.
	// The following tests for it
	const bool waitingForEndDialog = 
		msgId != MSG_END_DIALOG && 
		!m_dialogMutex.tryLock();

	if ( waitingForEndDialog ) {
		LOG_DEBUG("A doDialog--endDialog sequence has not ended yet. "
			"Message id: %i", msgId);
		m_shouldBreak = true;
		return;
	}

	// MSG_DO_DIALOG message should lock the mutex (the current state),
	// all other messages except MSG_END_DIALOG unlock it.
	if (msgId == MSG_DO_DIALOG) {
	}
	else {
		m_dialogMutex.unlock();
	}
}

DialogLocker::~DialogLocker()
{
	// Dialog is closed, the mutex can be unlocked
	if (m_msgId == MSG_END_DIALOG) {
		m_dialogMutex.unlock();
	}	
}

bool DialogLocker::shouldBreak() const
{
	return m_shouldBreak;
}

}