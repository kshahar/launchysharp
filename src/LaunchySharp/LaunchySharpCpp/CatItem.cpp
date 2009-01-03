#include "CatItem.h"

namespace LaunchySharpCpp
{

/// The full path of the file to execute
System::String^ CatItem::getFullPath()
{
	return m_fullPath;
}

/// The abbreviated name of the indexed item.
System::String^ CatItem::getShortName()
{
	return m_shortName;
}

/// The lowercase name of the indexed item.
System::String^ CatItem::getLowName()
{
	return m_lowName;
}

/// A path to an icon for the item.
System::String^ CatItem::getIconPath()
{
	return m_iconPath;
}

/// How many times this item has been called by the user.
int CatItem::getUsage()
{
	return m_usage;
}

/// The plugin id of the creator of this CatItem (0 for Launchy itself).
int CatItem:: getID()
{
	return m_id;
}

}