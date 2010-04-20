#include "Precompiled.h"
#include "LaunchySharpPlugin/InPluginLocker.h"

#include <QtCore/QMutex>

namespace LaunchySharpPlugin
{

InPluginLocker::InPluginLocker(QMutex& inPluginMutex)
: m_inPluginMutex(inPluginMutex)
{
	// Avoiding the scenario where a plugin function is called while another
	// one hasn't returned yet. Not sure it's the best way.
	const bool waitingForPluginFunctionToReturn = !m_inPluginMutex.tryLock();
	if ( waitingForPluginFunctionToReturn ) { 
		LOG_DEBUG("Trying to call a plugin function while another one hasn't "
			"returned yet. Message id: %i, msgId");
		return; 
	}
}

InPluginLocker::~InPluginLocker()
{
	// Out of plugin function, unlock the mutex
	m_inPluginMutex.unlock();
}

}