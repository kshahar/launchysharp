#pragma once

#include <QtCore/QList>
#include "catalog.h"

namespace Launchy 
{
	class Plugin {
	public:
		virtual ~Plugin() {}
		virtual void init() = 0;
		virtual void getID(uint*) = 0;
		virtual void getName(QString*) = 0;
		virtual void getLabels(QList<InputData>*) = 0;
		virtual void getResults(QList<InputData>* id, QList<CatItem>* results) = 0;
		virtual void getCatalog(QList<CatItem>* items) = 0;
		virtual void launchItem(QList<InputData>*, CatItem*) = 0;
		virtual bool hasDialog() = 0;
		virtual void doDialog(QWidget* parent, QWidget**) = 0;
		virtual void endDialog(bool accept) = 0;
		virtual void launchyShow() = 0;
		virtual void launchyHide() = 0;
	};
}
