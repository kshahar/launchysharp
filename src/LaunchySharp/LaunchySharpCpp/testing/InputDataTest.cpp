#include "Precompiled.h"
#ifdef LaunchySharp_TESTING

#include "LaunchySharpCpp/InputData.h"
#include "LaunchySharpCpp/CatItemConverter.h"

using namespace NUnit::Framework;
using namespace NUnit::Mocks;
using namespace System::Collections::Generic;

namespace LaunchySharpCpp
{
namespace testing 
{
	[TestFixture]
	public ref class InputDataTest
	{
	private:
		::InputData* pLaunchyInputData;
		LaunchySharpCpp::CatItemConverter* pCatItemConverter;
		LaunchySharpCpp::InputData^ inputData;

	public:
		[SetUp]
		void setUp()
		{
			pLaunchyInputData = new ::InputData();
			pCatItemConverter = new LaunchySharpCpp::CatItemConverter();
			inputData = gcnew LaunchySharpCpp::InputData(
				*pLaunchyInputData, *pCatItemConverter);
		}

		[TearDown]
		void tearDown()
		{
			delete pLaunchyInputData;
			delete pCatItemConverter;
		}

		[Test]
		void testSetLabel()
		{
			inputData->setLabel(888);
			Assert::IsTrue( pLaunchyInputData->hasLabel(888) );
		}

		[Test]
		void testHasLabel()
		{
			pLaunchyInputData->setLabel(999);
			Assert::IsTrue( inputData->hasLabel(999) );
		}

		[Test]
		void testSetID()
		{
			inputData->setID(888);
			Assert::IsTrue( pLaunchyInputData->getID() == 888 );
		}

		[Test]
		void testGetID()
		{
			pLaunchyInputData->setID(999);
			Assert::IsTrue( inputData->getID() == 999 );
		}

		[Test]
		void testSetText()
		{
			inputData->setText(L"LABEL");
			Assert::IsTrue( pLaunchyInputData->getText() == "LABEL" );
		}

		[Test]
		void testGetText()
		{
			pLaunchyInputData->setText("LABEL");
			Assert::AreEqual( inputData->getText(), L"LABEL" );
		}

		[Test]
		void testGetTopResult()
		{
			::CatItem launchyTopResult;
			launchyTopResult.fullPath = "fullpath";
			launchyTopResult.shortName = "shortname";
			launchyTopResult.lowName = "lowname";
			launchyTopResult.icon = "icon";
			launchyTopResult.usage = 12;
			launchyTopResult.data = 0;
			launchyTopResult.id = 999;
			pLaunchyInputData->setTopResult(launchyTopResult);
			
			LaunchySharp::ICatItem^ topResult = 
				inputData->getTopResult();
			
			Assert::IsTrue( topResult == launchyTopResult );
		}

		[Test]
		void testSetTopResult()
		{
			LaunchySharp::ICatItem^ topResult = 
				gcnew LaunchySharpCpp::CatItem(L"FULL", L"SHORT", 15, L"ICON");
			inputData->setTopResult(topResult);

			::CatItem launchyTopResult = pLaunchyInputData->getTopResult();

			Assert::IsTrue( topResult == launchyTopResult );
		}
	};


}
}

#endif