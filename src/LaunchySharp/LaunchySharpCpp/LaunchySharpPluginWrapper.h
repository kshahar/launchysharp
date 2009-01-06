#pragma once

#include <Launchy/Plugin.h>
#include <msclr/auto_gcroot.h>
#include <gcroot.h>

namespace LaunchySharpCpp
{
	class CatItemConverter;
	class InputDataListConverter;

	class LaunchySharpPluginWrapper: public Launchy::Plugin
	{
	public:
		LaunchySharpPluginWrapper(
			LaunchySharp::IPlugin^ plugin,
			LaunchySharp::IPluginHost^ pluginHost,
			CatItemConverter& catItemConverter,
			InputDataListConverter& inputDataListConverter);

		virtual void init();

		virtual void getID(uint* pId);

		virtual void getName(QString* pName);

		virtual void getLabels(QList<::InputData>*);

		virtual void getResults(QList<::InputData>* id, QList<::CatItem>* results);

		virtual void getCatalog(QList<::CatItem>* items);

		virtual void launchItem(QList<::InputData>*, ::CatItem*);

		virtual bool hasDialog();

		virtual void doDialog(QWidget* parent, QWidget**);

		virtual void endDialog(bool accept);	

		virtual void launchyShow();

		virtual void launchyHide();

		// Should not be used in production
		void setPluginForTesting(LaunchySharp::IPlugin^ plugin);

	private:
		msclr::auto_gcroot< LaunchySharp::IPlugin^ > m_plugin;
		gcroot< LaunchySharp::IPluginHost^ > m_pluginHost;
		CatItemConverter& m_catItemConverter;
		InputDataListConverter& m_inputDataListConverter;
	};
}