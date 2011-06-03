#include "Precompiled.h"

#include "LaunchySharpCpp/LaunchySharpPluginWrapper.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapperFactory.h"
#include "LaunchySharpCpp/StringConversions.h"
#include "LaunchySharpCpp/testing/EmptyLaunchySharpPlugin.h"
#include "LaunchySharpCpp/testing/FakePluginHost.h"
#include "LaunchySharpCpp/testing/FakeOptionsWidgetHandler.h"

using namespace NUnit::Framework;
using namespace NUnit::Mocks;
using namespace System::Collections::Generic;

namespace LaunchySharpCpp
{
namespace testing 
{
	ref class PluginWithGetLabels: EmptyLaunchySharpPlugin
	{
	public:
		unsigned int labelId;
		virtual void getLabels(
			System::Collections::Generic::List<LaunchySharp::IInputData^>^ inputDataList) override
		{
			for each (LaunchySharp::IInputData^ inputData in inputDataList)
			{
				inputData->setLabel(labelId);
			}
		}

	};

	[TestFixture]
	public ref class LaunchySharpPluginWrapperTest
	{
	private:
		DynamicMock^ m_pluginMock;
		LaunchySharp::IPluginHost^ m_fakePluginHost;
		LaunchySharpCpp::IOptionsWidgetHandler* m_fakeOptionsWidgetHandler;
		LaunchySharpCpp::LaunchySharpPluginWrapper* m_pWrapper;
		LaunchySharpCpp::LaunchySharpPluginWrapperFactory* m_pPluginWrapperFactory;
		
	public:
		[SetUp]
		void setUp()
		{
			m_pluginMock = 
				gcnew DynamicMock(LaunchySharp::IPlugin::typeid);

			m_fakePluginHost = gcnew FakePluginHost();

			m_fakeOptionsWidgetHandler = new FakeOptionsWidgetHandler();

			m_pPluginWrapperFactory = 
				new LaunchySharpCpp::LaunchySharpPluginWrapperFactory(
					m_fakePluginHost, *m_fakeOptionsWidgetHandler);

			Launchy::Plugin* wrapper = m_pPluginWrapperFactory->create(
				(LaunchySharp::IPlugin^)m_pluginMock->MockInstance);
			m_pWrapper = dynamic_cast<LaunchySharpPluginWrapper*>(wrapper);

			Assert::IsTrue(m_pWrapper != NULL);
		}
		[TearDown]
		void tearDown()
		{
			delete m_pPluginWrapperFactory;
			delete m_fakeOptionsWidgetHandler;
		}

		[Test]
		void testInit()
		{
			m_pluginMock->Expect("init");
			m_pWrapper->init();
			m_pluginMock->Verify();				
		}

		[Test]
		void testGetID()
		{
			unsigned int id;
			System::UInt32 idToExpect = 100;
			m_pluginMock->Expect("getID");
			m_pluginMock->SetReturnValue("getID", idToExpect);
			m_pWrapper->getID(&id);
			m_pluginMock->Verify();

			Assert::AreEqual( idToExpect, System::UInt32(id) );			
		}

		[Test]
		void testGetName()
		{
			QString name;
			System::String^ nameToExpect = L"MockPlugin";
			m_pluginMock->Expect("getName");
			m_pluginMock->SetReturnValue("getName", nameToExpect);
			m_pWrapper->getName(&name);
			m_pluginMock->Verify();

			Assert::AreEqual( nameToExpect, QStringToString(name) );
		}

		[Test]
		void testGetLabelsIsCalled()
		{
			QList<::InputData> inputDataList;
			m_pluginMock->Expect("getLabels");
			m_pWrapper->getLabels(&inputDataList);
			m_pluginMock->Verify();			
		}

		[Test]
		void testGetLabels()
		{
			const unsigned int labelId = 999;
			QList<::InputData> inputDataList;
			PluginWithGetLabels^ pluginWithGetLabels = gcnew PluginWithGetLabels;
			m_pWrapper->setPluginForTesting(pluginWithGetLabels);
			pluginWithGetLabels->labelId = labelId;
			inputDataList.append( InputData("ABC") );
			inputDataList.append( InputData("EFG") );
			m_pWrapper->getLabels(&inputDataList);
			for (int i=0; i<inputDataList.size(); ++i) {
				Assert::IsTrue( inputDataList[i].hasLabel( labelId ) );
			}
		}

		[Test]
		void testGetResults()
		{
			QList<::InputData> inputDataList;
			QList<::CatItem> resultsList;
			m_pluginMock->Expect("getResults");
			m_pWrapper->getResults(&inputDataList, &resultsList);
			m_pluginMock->Verify();
		}

		[Test]
		void testGetCatalog()
		{
			QList<::CatItem> catalogItemsList;
			m_pluginMock->Expect("getCatalog");
			m_pWrapper->getCatalog(&catalogItemsList);
			m_pluginMock->Verify();
		}

		[Test]
		void testLaunchItem()
		{
			QList<::InputData> inputDataList;
			::CatItem itemToLaunch;
			m_pluginMock->Expect("launchItem");
			m_pWrapper->launchItem(&inputDataList, &itemToLaunch);
			m_pluginMock->Verify();
		}

		[Test]
		void testEndDialog()
		{
			m_pluginMock->Expect("endDialog");
			m_pWrapper->endDialog(true);
			m_pluginMock->Verify();
		}

		[Test]
		void testLaunchyShow()
		{
			m_pluginMock->Expect("launchyShow");
			m_pWrapper->launchyShow();
			m_pluginMock->Verify();
		}

		[Test]
		void testLaunchyHide()
		{
			m_pluginMock->Expect("launchyHide");
			m_pWrapper->launchyHide();
			m_pluginMock->Verify();
		}

		[Test]
		void testSetPath()
		{
			m_pluginMock->Expect("setPath");
			QString path("temp");
			m_pWrapper->setPath(&path);
			m_pluginMock->Verify();
		}
	};
}
}
