#include "Precompiled.h"
#include "LaunchySharpPlugin/LaunchyPluginWrapper.h"
#include "Launchy/Plugin.h"

namespace LaunchySharpPlugin
{

LaunchyPluginWrapper::LaunchyPluginWrapper(Launchy::Plugin& plugin)
: m_plugin(plugin)
{

}

LaunchyPluginWrapper::~LaunchyPluginWrapper()
{

}

int LaunchyPluginWrapper::msg(int msgId, void* wParam, void* lParam)
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

}