#pragma once

#include "Launchy/Plugin.h"

namespace LaunchySharpCpp 
{
namespace testing
{

	class EmptyLaunchyPlugin: public Launchy::Plugin {
	public:
		virtual void init() {}
		virtual void getID(uint*) {}
		virtual void getName(QString*) {}
		virtual void getLabels(QList<InputData>*) {}
		virtual void getResults(QList<InputData>* id, QList<CatItem>* results) {}
		virtual void getCatalog(QList<CatItem>* items) {}
		virtual void launchItem(QList<InputData>*, CatItem*) {}
		virtual bool hasDialog() {return false;}
		virtual void doDialog(QWidget* parent, QWidget**) {}
		virtual void endDialog(bool accept) {}
		virtual void launchyShow() {}
		virtual void launchyHide() {}
	};

}
}