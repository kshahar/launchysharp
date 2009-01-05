#include "Precompiled.h"
#include "LaunchySharpCpp/LaunchySharpPluginWrapper.h"
#include "LaunchySharpCpp/StringConversions.h"
#include "LaunchySharpCpp/InputDataFactory.h"
#include "LaunchySharpCpp/InputDataListConverter.h"

using namespace NUnit::Framework;
using namespace NUnit::Mocks;
using namespace System::Collections::Generic;

namespace LaunchySharpCpp 
{
	ref class EmptyPlugin: LaunchySharp::IPlugin
	{
	public:
		virtual void init(LaunchySharp::IPluginHost^ pluginHost)
		{
		}
		virtual int getID()
		{
			return 0;
		}
		virtual System::String^ getName()
		{
			return gcnew System::String(L"");
		}
		virtual void getLabels(
			List<LaunchySharp::IInputData^>^ inputDataList)
		{
		}
		virtual void getResults(
			List<LaunchySharp::IInputData^>^ inputDataList, 
			List<LaunchySharp::ICatItem^>^ resultsList)
		{	
		}
		virtual void getCatalog(
			List<LaunchySharp::ICatItem^>^ catalogItems)
		{	
		}
		virtual void launchItem(
			List<LaunchySharp::IInputData^>^ inputDataList, 
			LaunchySharp::ICatItem^ item)
		{	
		}
	};
}

namespace LaunchySharpCpp
{
namespace testing 
{
	ref class PluginWithGetLabels: LaunchySharpCpp::EmptyPlugin
	{
	public:
		unsigned int labelId;
		virtual void getLabels(
			List<LaunchySharp::IInputData^>^ inputDataList) override
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
		LaunchySharpCpp::LaunchySharpPluginWrapper* m_pWrapper;
		LaunchySharpCpp::InputDataFactory* m_pInputDataFactory;
		LaunchySharpCpp::InputDataListConverter* m_pInputDataListConverter;

	public:
		[SetUp]
		void setUp()
		{
			m_pluginMock = 
				gcnew DynamicMock(LaunchySharp::IPlugin::typeid);
			m_pInputDataFactory = new LaunchySharpCpp::InputDataFactory();
			m_pInputDataListConverter = 
				new LaunchySharpCpp::InputDataListConverter( *m_pInputDataFactory );
			m_pWrapper = new LaunchySharpCpp::LaunchySharpPluginWrapper(
				(LaunchySharp::IPlugin^)m_pluginMock->MockInstance,
				*m_pInputDataListConverter);
		}
		[TearDown]
		void tearDown()
		{
			delete m_pWrapper;
			delete m_pInputDataListConverter;
			delete m_pInputDataFactory;
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
			System::Int32 idToExpect = 100;
			m_pluginMock->Expect("getID");
			m_pluginMock->SetReturnValue("getID", idToExpect);
			m_pWrapper->getID(&id);
			m_pluginMock->Verify();

			Assert::AreEqual( idToExpect, System::Int32(id) );			
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
	};
}
}