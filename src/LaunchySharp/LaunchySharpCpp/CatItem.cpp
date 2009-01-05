#include "Precompiled.h"
#include "CatItem.h"
#include <LaunchySharpCpp/StringConversions.h>

namespace LaunchySharpCpp
{

bool operator==(::CatItem& launchyCatItem, LaunchySharp::ICatItem^ sharpCatItem)
{
	return 
		launchyCatItem.fullPath == StringToQString(sharpCatItem->getFullPath()) &&
		launchyCatItem.shortName == StringToQString(sharpCatItem->getShortName()) &&
		launchyCatItem.lowName == StringToQString(sharpCatItem->getLowName()) &&
		launchyCatItem.icon == StringToQString(sharpCatItem->getIconPath()) &&
		launchyCatItem.usage == sharpCatItem->getUsage() &&
		launchyCatItem.id == sharpCatItem->getID();
}

bool operator==(LaunchySharp::ICatItem^ sharpCatItem, ::CatItem& launchyCatItem)
{
	return launchyCatItem == sharpCatItem;
}

CatItem::CatItem(System::String^ full, System::String^ shortN)
{
	m_fullPath = full;
	m_shortName = shortN;
	m_lowName = shortN->ToLower();
	m_iconPath = L"";
	m_usage = 0;
	m_id = 0;
}

CatItem::CatItem(System::String^ full, System::String^ shortN, unsigned int id)
{
	m_fullPath = full;
	m_shortName = shortN;
	m_lowName = shortN->ToLower();
	m_iconPath = L"";
	m_usage = 0;
	m_id = id;
}

CatItem::CatItem(System::String^ full, System::String^ shortN, unsigned int id, System::String^ iconPath)
{
	m_fullPath = full;
	m_shortName = shortN;
	m_lowName = shortN->ToLower();
	m_iconPath = L"";
	m_usage = 0;
	m_id = id;
}

CatItem::CatItem( System::String^ full, System::String^ shortN, unsigned int id, 
				 System::String^ iconPath, unsigned int usage, System::String^ lowName )
{
	m_fullPath = full;
	m_shortName = shortN;
	m_lowName = lowName;
	m_iconPath = iconPath;
	m_usage = usage;
	m_id = id;
}

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