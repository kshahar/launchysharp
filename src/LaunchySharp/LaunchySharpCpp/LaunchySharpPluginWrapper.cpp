#include "Precompiled.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapper.h"
#include "LaunchySharpCpp/InputData.h"
#include "LaunchySharpCpp/StringConversions.h"
#include "LaunchySharpCpp/InputDataListConverter.h"

using namespace System::Collections::Generic;

namespace LaunchySharpCpp {

LaunchySharpPluginWrapper::LaunchySharpPluginWrapper(
	LaunchySharp::IPlugin^ plugin, InputDataListConverter& inputDataListConverter)
: m_plugin(plugin), 
  m_inputDataListConverter(inputDataListConverter)
{
}

void LaunchySharpPluginWrapper::init()
{
	m_plugin->init(nullptr);
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
	List<LaunchySharp::IInputData^>^ inputDataList =
		m_inputDataListConverter.fromLaunchy(*pInputDataList);
	m_plugin->getLabels(inputDataList);
}

void LaunchySharpPluginWrapper::getResults(
	QList<::InputData>* pInputDataList, QList<::CatItem>* pResultsList)
{
	m_plugin->getResults(nullptr, nullptr);
}

void LaunchySharpPluginWrapper::getCatalog(QList<::CatItem>* pCatalogItems)
{
	m_plugin->getCatalog(nullptr);
}

void LaunchySharpPluginWrapper::launchItem(
	QList<::InputData>* pInputDataList, ::CatItem* pItemToLaunch)
{
	m_plugin->launchItem(nullptr, nullptr);
}

bool LaunchySharpPluginWrapper::hasDialog()
{
	return false;
}

void LaunchySharpPluginWrapper::doDialog(QWidget* parent, QWidget**)
{
	// Not Implemented
}

void LaunchySharpPluginWrapper::endDialog(bool accept)
{
	// Not Implemented
}

void LaunchySharpPluginWrapper::launchyShow()
{
	// Not Implemented
}

void LaunchySharpPluginWrapper::launchyHide()
{
	// Not Implemented
}

void LaunchySharpPluginWrapper::setPluginForTesting(LaunchySharp::IPlugin^ plugin)
{
	m_plugin = plugin;
}

}