#include "Precompiled.h"

#include "LaunchySharpCpp/CatItemFactory.h"

using namespace NUnit::Framework;
using namespace NUnit::Mocks;

namespace LaunchySharpCpp
{
namespace testing 
{
	[TestFixture]
	public ref class CatItemFactoryTest
	{
	private:
		CatItemFactory^ catItemFactory;

	public:
		[SetUp]
		void setUp()
		{
			catItemFactory = gcnew CatItemFactory();
		}

		[Test]
		void test4ParametersConstructor()
		{
			System::String^ fullPath = "fullPath";
			System::String^ shortName = "shortName";
			unsigned int id = 999;
			System::String^ iconPath = "iconPath";

			LaunchySharp::ICatItem^ catITem = 
				catItemFactory->createCatItem(fullPath, shortName, id, iconPath);

			Assert::AreEqual(catITem->getFullPath(), fullPath);
			Assert::AreEqual(catITem->getShortName(), shortName);
			Assert::AreEqual(catITem->getID(), id);
			Assert::AreEqual(catITem->getIconPath(), iconPath);
		}

		[Test]
		void test5ParametersConstructor()
		{
			// Ugly... duplication of the 4 parameters test
			System::String^ fullPath = "fullPath";
			System::String^ shortName = "shortName";
			unsigned int id = 999;
			System::String^ iconPath = "iconPath";
			unsigned int usage = 17;

			LaunchySharp::ICatItem^ catITem = 
				catItemFactory->createCatItem(fullPath, shortName, id, 
					iconPath, usage);

			Assert::AreEqual(catITem->getFullPath(), fullPath);
			Assert::AreEqual(catITem->getShortName(), shortName);
			Assert::AreEqual(catITem->getID(), id);
			Assert::AreEqual(catITem->getIconPath(), iconPath);
			Assert::IsTrue(catITem->getUsage() == usage);
		}
	};
}
}