#pragma once

namespace LaunchySharpCpp 
{
	ref class TestPlugin: LaunchySharp::IPlugin
	{
	public:
		virtual void init()
		{
		}

		virtual int getID()
		{
			return 8844233;
		}

		virtual System::String^ getName()
		{
			return gcnew System::String(L"TestPlugin");
		}

		virtual System::String^ getIcon()
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
	};
}