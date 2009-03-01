#include "Precompiled.h"
#include "LaunchySharpPlugin/LaunchyPluginWrapper.h"
#include "Launchy/Plugin.h"

#define PLUGIN_DEBUG

#ifdef PLUGIN_DEBUG
#include <QtCore/QTextStream>

struct PluginDebug {
	PluginDebug()
		: debugFile("c:\\LaunchySharpDebug.txt"),
		  debugStream(&debugFile)
	{
		if (!debugFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
		}
	}

	QFile debugFile;
	QTextStream debugStream;
};
static PluginDebug g_pluginDebug;

#define LOG_DEBUG(logExpr) \
	do { \
		g_pluginDebug.debugStream << (logExpr) << "\n"; \
		g_pluginDebug.debugStream.flush(); \
		g_pluginDebug.debugStream.flush(); \
	} while(0);
#else
#define LOG_DEBUG(logExpr) \
	do {} while(0);
#endif

namespace LaunchySharpPlugin
{

//! RAII-style locker for dialog functions
class DialogLocker {
public:
	DialogLocker(int msgId, QMutex& dialogMutex);
	~DialogLocker();
	bool shouldBreak;
private:
	int m_msgId;
	QMutex& m_dialogMutex;
};

//! RAII-style locker for all plugin functions
class InPluginLocker {
public:
	InPluginLocker(QMutex& inPluginMutex);
	~InPluginLocker();
	bool shouldBreak;
private:
	int m_msgId;
	QMutex& m_inPluginMutex;
};

LaunchyPluginWrapper::LaunchyPluginWrapper(Launchy::Plugin& plugin)
: m_plugin(plugin)
{

}

LaunchyPluginWrapper::~LaunchyPluginWrapper()
{

}

int LaunchyPluginWrapper::msg(int msgId, void* wParam, void* lParam)
{
	return synchronizedDispatch(msgId, wParam, lParam);
}

bool LaunchyPluginWrapper::synchronizedDispatch(int msgId, void* wParam, 
	void* lParam)
{
	// Handle locks
	
	DialogLocker dialogLocker(msgId, m_dialogMutex);
	if (dialogLocker.shouldBreak) {
		return false;
	}

	InPluginLocker inPluginLocker(m_inPluginMutex);

	// Disptach the actual Python function
	const bool result = dispatchFunction(msgId, wParam, lParam);

	return result;
}

bool LaunchyPluginWrapper::dispatchFunction(int msgId, void* wParam, 
	void* lParam)
{
	bool handled = false;

	switch (msgId)
	{		
		case MSG_INIT:
			m_plugin.init();
			handled = true;
			break;
		case MSG_GET_LABELS:
			m_plugin.getLabels((QList<InputData>*) wParam);
			handled = true;
			break;
		case MSG_GET_ID:
			m_plugin.getID((uint*) wParam);
			handled = true;
			break;
		case MSG_GET_NAME:
			m_plugin.getName((QString*) wParam);
			handled = true;
			break;
		case MSG_GET_RESULTS:
			m_plugin.getResults((QList<InputData>*) wParam, (QList<CatItem>*) lParam);
			handled = true;
			break;
		case MSG_GET_CATALOG:
			m_plugin.getCatalog((QList<CatItem>*) wParam);
			handled = true;
			break;
		case MSG_LAUNCH_ITEM:
			m_plugin.launchItem((QList<InputData>*) wParam, (CatItem*) lParam);
			handled = true;
			break;
		case MSG_HAS_DIALOG:
			// Set to true if you provide a gui
			handled = m_plugin.hasDialog();
			break;
		case MSG_DO_DIALOG:
			// This isn't called unless you return true to MSG_HAS_DIALOG
			m_plugin.doDialog((QWidget*) wParam, (QWidget**) lParam);
			break;
		case MSG_END_DIALOG:
			// This isn't called unless you return true to MSG_HAS_DIALOG
			m_plugin.endDialog((bool) wParam);
			break;
		case MSG_LAUNCHY_SHOW:
			handled = true;
			m_plugin.launchyShow();
			break;
		case MSG_LAUNCHY_HIDE:
			handled = true;
			m_plugin.launchyHide();
			break;

		default:
			break;
	}

	return handled;
}

/***************************************/
// DialogLocker
/***************************************/
DialogLocker::DialogLocker(int msgId, QMutex& dialogMutex)
: m_dialogMutex(dialogMutex), 
  m_msgId(msgId), 
  shouldBreak(false)
{
	// We can't allow plugin functions to be called when doDialog was called
	// and endDialog not called yet, since it is dangerous.
	// The following tests for it
	const bool waitingForEndDialog = 
		msgId != MSG_END_DIALOG && 
		!m_dialogMutex.tryLock();

	if ( waitingForEndDialog ) {
		LOG_DEBUG("A doDialog--endDialog sequence has not ended yet. "
			"Message id: %i, msgId");
		shouldBreak = true;
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

/***************************************/
// InPluginLocker
/***************************************/
InPluginLocker::InPluginLocker(QMutex& inPluginMutex)
: m_inPluginMutex(inPluginMutex),
  shouldBreak(false)
{
	// Avoiding the scenario where a plugin function is called while another
	// one hasn't returned yet. Not sure it's the best way.
	const bool waitingForPluginFunctionToReturn = !m_inPluginMutex.tryLock();
	if ( waitingForPluginFunctionToReturn ) { 
		LOG_DEBUG("Trying to call a plugin function while another one hasn't "
			"returned yet. Message id: %i, msgId");
		shouldBreak = true;
		return; 
	}
}

InPluginLocker::~InPluginLocker()
{
	// Out of plugin function, unlock the mutex
	m_inPluginMutex.unlock();
}

}