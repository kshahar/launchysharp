#pragma once

#include "Launchy/Catalog.h"

namespace LaunchySharpCpp
{
	ref class CatItem: LaunchySharp::ICatItem
	{
	public:
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
		virtual int getID();

	private:
		System::String^ m_fullPath;
		System::String^ m_shortName;
		System::String^ m_lowName;
		System::String^ m_iconPath;
		int m_usage;
		int m_id;
	};
}