#pragma once

namespace LaunchySharpCpp 
{
namespace testing
{

	ref class EmptyLaunchySharpPlugin: LaunchySharp::IPlugin
	{
	public:
		virtual void init(LaunchySharp::IPluginHost^ pluginHost)
		{
		}
		virtual unsigned int getID()
		{
			return 0;
		}
		virtual System::String^ getName()
		{
			return gcnew System::String(L"");
		}
		virtual void getLabels(
			System::Collections::Generic::List<LaunchySharp::IInputData^>^ inputDataList)
		{
		}
		virtual void getResults(
			System::Collections::Generic::List<LaunchySharp::IInputData^>^ inputDataList, 
			System::Collections::Generic::List<LaunchySharp::ICatItem^>^ resultsList)
		{	
		}
		virtual void getCatalog(
			System::Collections::Generic::List<LaunchySharp::ICatItem^>^ catalogItems)
		{	
		}
		virtual void launchItem(
			System::Collections::Generic::List<LaunchySharp::IInputData^>^ inputDataList, 
			LaunchySharp::ICatItem^ item)
		{	
		}
		virtual bool hasDialog()
		{
			return false;
		}
		virtual System::IntPtr doDialog()
		{
			return System::IntPtr::Zero;
		}
		virtual void endDialog(bool acceptedByUser)
		{
		}
		virtual void launchyShow()
		{
		}
		virtual void launchyHide()
		{
		}
		
		virtual void setPath(System::String^)
		{
		}
	};

}
}