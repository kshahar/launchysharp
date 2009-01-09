#include "Precompiled.h"

#include "LaunchySharpCpp/FilePluginLoader.h"
#include "LaunchySharpCpp/PluginFactory.h"
#include "LaunchySharpCpp/testing/EmptyLaunchyPlugin.h"
#include "LaunchySharpCpp/testing/EmptyLaunchySharpPlugin.h"
#include "LaunchySharpCpp/StringConversions.h"

using namespace NUnit::Framework;
using namespace NUnit::Mocks;
using namespace System::Collections::Generic;



namespace LaunchySharpCpp
{
namespace testing 
{
	class LaunchyPluginWithName: public EmptyLaunchyPlugin {
	public:
		QString name;
		LaunchyPluginWithName(const QString& name_): name(name_) {}
		virtual void getName(QString* pName) {*pName = name;}
	};

	ref class LaunchySharpPluginWithName: public EmptyLaunchySharpPlugin {
	public:
		System::String^ name;
		LaunchySharpPluginWithName(System::String^ name_): name(name_) {}
		virtual System::String^ getName() override { return name; }
	};

	ref class FakePluginLoader: public IPluginLoader {
	public:
		virtual LaunchySharp::IPlugin^ loadPlugin(System::String^ fileName)
		{
			return gcnew LaunchySharpPluginWithName(fileName);
		}
	};

	class FakePluginFactory: public LaunchySharpCpp::PluginFactory {
	public:
		virtual Launchy::Plugin* create(LaunchySharp::IPlugin^ plugin)
		{
			System::String^ name = plugin->getName();
			return new LaunchyPluginWithName(StringToQString(name));
		}
	};

	[TestFixture]
	public ref class FilePluginLoaderTest
	{
	private:
		PluginFactory* m_pPluginFactory;
		IPluginLoader^ m_pluginLoader;
		FilePluginLoader* m_pFilePluginLoader;
		Launchy::Plugin* m_pResultPlugin;

	public:
		[SetUp]
		void setUp()
		{
			m_pPluginFactory = new FakePluginFactory();
			m_pluginLoader = gcnew FakePluginLoader();
			m_pFilePluginLoader = new FilePluginLoader(
				m_pluginLoader, *m_pPluginFactory);
			m_pResultPlugin = NULL;
		}

		[TearDown]
		void tearDown()
		{
			delete m_pPluginFactory;
			delete m_pFilePluginLoader;
			delete m_pResultPlugin;
		}

		[Test]
		void testLoadPlugin()
		{
			const QString fileName = "no_such_file1.dll";
			m_pResultPlugin = m_pFilePluginLoader->loadPlugin( fileName );

			Assert::IsTrue( m_pResultPlugin != NULL );

			QString name;
			m_pResultPlugin->getName(&name);
			Assert::IsTrue( name == fileName );
		}
	};
}

}
