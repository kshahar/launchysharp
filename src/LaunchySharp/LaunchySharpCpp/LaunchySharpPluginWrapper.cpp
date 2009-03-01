#include "Precompiled.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapper.h"
#include "LaunchySharpCpp/StringConversions.h"
#include "LaunchySharpCpp/CatItemConverter.h"
#include "LaunchySharpCpp/InputDataListConverter.h"

using namespace System::Collections::Generic;

#define GUARDED_CALL_TO_PLUGIN(expr) do { \
		try { \
			expr \
		} \
		catch(System::Exception^ exception) { \
			exception->ToString(); \
		} \
	} while (0); \
//

namespace LaunchySharpCpp {

LaunchySharpPluginWrapper::LaunchySharpPluginWrapper(
	LaunchySharp::IPlugin^ plugin, 
	LaunchySharp::IPluginHost^ pluginHost,
	CatItemConverter& catItemConverter,
	InputDataListConverter& inputDataListConverter)
: m_plugin(plugin), 
  m_pluginHost(pluginHost),
  m_catItemConverter(catItemConverter),
  m_inputDataListConverter(inputDataListConverter)
{
}

void LaunchySharpPluginWrapper::init()
{
	GUARDED_CALL_TO_PLUGIN
	(
		m_plugin->init(m_pluginHost);
	);
}

void LaunchySharpPluginWrapper::getID(uint* pId)
{
	GUARDED_CALL_TO_PLUGIN
	(
		*pId = m_plugin->getID();
	)
}

void LaunchySharpPluginWrapper::getName(QString* pName)
{
	GUARDED_CALL_TO_PLUGIN
	(
		System::String^ name = m_plugin->getName();
		*pName = StringToQString(name);
	);
}

void LaunchySharpPluginWrapper::getLabels(QList<::InputData>* pInputDataList)
{
	List<LaunchySharp::IInputData^>^ inputDataList =
		m_inputDataListConverter.fromLaunchy(*pInputDataList);

	GUARDED_CALL_TO_PLUGIN
	(
		m_plugin->getLabels(inputDataList);
	);
}

void LaunchySharpPluginWrapper::getResults(
	QList<::InputData>* pInputDataList, QList<::CatItem>* pResultsList)
{
	List<LaunchySharp::IInputData^>^ inputDataList =
		m_inputDataListConverter.fromLaunchy(*pInputDataList);
	List<LaunchySharp::ICatItem^>^ resultsList = 
		gcnew List<LaunchySharp::ICatItem^>;

	GUARDED_CALL_TO_PLUGIN
	(
		m_plugin->getResults(inputDataList, resultsList);
	);

	for each (LaunchySharp::ICatItem^ catItem in resultsList) {
		pResultsList->append(
			m_catItemConverter.toLaunchy(catItem));
	}
}

void LaunchySharpPluginWrapper::getCatalog(QList<::CatItem>* pCatalogItems)
{
	List<LaunchySharp::ICatItem^>^ catalogItems = 
		gcnew List<LaunchySharp::ICatItem^>;

	GUARDED_CALL_TO_PLUGIN
	(
		m_plugin->getCatalog(catalogItems);
	);

	// TODO: Code duplication from above
	for each (LaunchySharp::ICatItem^ catItem in catalogItems) {
		pCatalogItems->append(
			m_catItemConverter.toLaunchy(catItem));
	}
}

void LaunchySharpPluginWrapper::launchItem(
	QList<::InputData>* pInputDataList, ::CatItem* pItemToLaunch)
{
	LaunchySharpCpp::CatItem^ itemToLaunch =
		m_catItemConverter.fromLaunchy(*pItemToLaunch);
	List<LaunchySharp::IInputData^>^ inputDataList =
		m_inputDataListConverter.fromLaunchy(*pInputDataList);

	GUARDED_CALL_TO_PLUGIN
	(
		m_plugin->launchItem(inputDataList, itemToLaunch);
	);
}

bool LaunchySharpPluginWrapper::hasDialog()
{
	return false;
}

void LaunchySharpPluginWrapper::doDialog(QWidget* parent, QWidget** pNewWidget)
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