#pragma once

#include "Launchy/Catalog.h"
namespace LaunchySharpCpp
{
	//! Compare Launchy CatItem to LaunchySharp::ICatItem
	bool operator==(::CatItem& launchyCatItem, LaunchySharp::ICatItem^ sharpCatItem);

	//! Compare Launchy CatItem to LaunchySharp::ICatItem
	bool operator==(LaunchySharp::ICatItem^ sharpCatItem, ::CatItem& launchyCatItem);

	ref class CatItem: LaunchySharp::ICatItem
	{
	public:
		CatItem(System::String^ full, System::String^ shortN);
		CatItem(System::String^ full, System::String^ shortN, unsigned int id);
		CatItem(System::String^ full, System::String^ shortN, unsigned int id, System::String^ iconPath);
		CatItem(System::String^ full, System::String^ shortN, unsigned int id,
			System::String^ iconPath, unsigned int usage);
		CatItem(System::String^ full, System::String^ shortN, unsigned int id,
			System::String^ iconPath, unsigned int usage, System::String^ lowName);

		/// The full path of the file to execute
		virtual System::String^ getFullPath();
		
		/// The abbreviated name of the indexed item.
		virtual System::String^ getShortName();
		
		/// The lowercase name of the indexed item.
		virtual System::String^ getLowName();
		
		/// A path to an icon for the item.
		virtual System::String^ getIconPath();
		
		/// How many times this item has been called by the user.
		virtual int getUsage();
		
		/// The plugin id of the creator of this CatItem (0 for Launchy itself).
		virtual unsigned int getID();

	private:
		System::String^ m_fullPath;
		System::String^ m_shortName;
		System::String^ m_lowName;
		System::String^ m_iconPath;
		int m_usage;
		unsigned int m_id;
	};
}