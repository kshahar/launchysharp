#include <gtest/gtest.h>
#include "LaunchySharpCpp/LaunchySharpPluginWrapper.h"

namespace LaunchySharp {
	using namespace System::Collections::Generic;

	namespace FakePluginFunctionsMask {
		enum Enum {
			init = 0x1,
			getID = 0x2,
			getName = 0x4,
			getIcon = 0x8,
			getLabels = 0x10,
			getResults = 0x20,
			getCatalog = 0x40,
			launchItem = 0x80
		};

		int totalMask = init | getID | getName ;//| getIcon | getLabels;
	}

	ref class FakePlugin: LaunchySharp::IPlugin
	{
	public:
		int mask;

		FakePlugin()
		{
			mask = 0;
		}

		virtual void init()
		{
			mask |= FakePluginFunctionsMask::init;
		}
		virtual int getID()
		{
			mask |= FakePluginFunctionsMask::getID;
			return 0;
		}
		virtual System::String^ getName()
		{
			mask |= FakePluginFunctionsMask::getName;
			return gcnew System::String(L"");
		}
		virtual System::String^ getIcon()
		{
			mask |= FakePluginFunctionsMask::getIcon;
			return gcnew System::String(L"");
		}
		virtual void getLabels(
			List<LaunchySharp::IInputData^>^ inputDataList)
		{
			mask |= FakePluginFunctionsMask::getLabels;
		}
		virtual void getResults(List<IInputData^>^ inputDataList, 
			List<ICatItem^>^ resultsList)
		{
			mask |= FakePluginFunctionsMask::getResults;
		}
		virtual void getCatalog(List<ICatItem^>^ catalogItems)
		{
			mask |= FakePluginFunctionsMask::getCatalog;
		}
		virtual void launchItem(List<IInputData^>^ inputDataList, ICatItem^ item)
		{
			mask |= FakePluginFunctionsMask::launchItem;
		}
	};
}

class LaunchySharpPluginWrapperTest: public testing::Test {
public:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(LaunchySharpPluginWrapperTest, AllFunctionsAreCalled)
{
	LaunchySharp::FakePlugin^ fakePlugin = 
		gcnew LaunchySharp::FakePlugin();
	LaunchySharpCpp::LaunchySharpPluginWrapper sharpWrapper(fakePlugin);

	unsigned int id;
	QString name;
	QList<::InputData> inputDataList;
	QList<::CatItem> catItemList;
	::CatItem catItem;

	sharpWrapper.init();
	sharpWrapper.getID(&id);
	sharpWrapper.getName(&name);
	sharpWrapper.getLabels(&inputDataList);
	sharpWrapper.getResults(&inputDataList, &catItemList);
	sharpWrapper.getCatalog(&catItemList);
	sharpWrapper.launchItem(&inputDataList, &catItem);
	sharpWrapper.hasDialog();
	sharpWrapper.doDialog(/*QWidget* parent*/NULL, /*QWidget***/NULL);
	sharpWrapper.endDialog(false);	
	sharpWrapper.launchyShow();
	sharpWrapper.launchyHide();

	EXPECT_EQ( 
		LaunchySharp::FakePluginFunctionsMask::totalMask, 
		fakePlugin->mask );
}
