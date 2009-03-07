#pragma once


namespace LaunchySharpCpp 
{
namespace testing
{
	ref class FakePluginHost: LaunchySharp::IPluginHost {
	public:
		virtual LaunchySharp::ICatItemFactory^ catItemFactory()
		{
			return nullptr;
		}

		virtual LaunchySharp::ILaunchyPaths^ launchyPaths()
		{
			return nullptr;
		}

		virtual unsigned int hash(System::String^)
		{
			return 0;
		}
	};
}
}