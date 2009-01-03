#include "LaunchySharpCpp/LaunchySharpPluginWrapper.h"
#include "LaunchySharpCpp/InputData.h"
#include "LaunchySharpCpp/StringConversions.h"

using namespace System::Collections::Generic;

namespace LaunchySharpCpp {

LaunchySharpPluginWrapper::LaunchySharpPluginWrapper(LaunchySharp::IPlugin^ plugin)
: m_plugin(plugin)
{
}

void LaunchySharpPluginWrapper::init()
{
	m_plugin->init();
}

void LaunchySharpPluginWrapper::getID(uint* pId)
{
	*pId = m_plugin->getID();
}

void LaunchySharpPluginWrapper::getName(QString* pName)
{
	System::String^ name = m_plugin->getName();
	*pName = StringToQString(name);
}

void LaunchySharpPluginWrapper::getLabels(QList<::InputData>* pInputDataList)
{
	//List< LaunchySharp::IInputData > inputDataList;
}

void LaunchySharpPluginWrapper::getResults(QList<::InputData>* id, QList<::CatItem>* results)
{
}

void LaunchySharpPluginWrapper::getCatalog(QList<::CatItem>* items)
{
}

void LaunchySharpPluginWrapper::launchItem(QList<::InputData>*, ::CatItem*)
{
}

bool LaunchySharpPluginWrapper::hasDialog()
{
	return false;
}

void LaunchySharpPluginWrapper::doDialog(QWidget* parent, QWidget**)
{
}

void LaunchySharpPluginWrapper::endDialog(bool accept)
{
}

void LaunchySharpPluginWrapper::launchyShow()
{
}

void LaunchySharpPluginWrapper::launchyHide()
{
}

}