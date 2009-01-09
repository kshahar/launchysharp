#include "Precompiled.h"
#include "LaunchySharpCpp/CatItemConverter.h"
#include "LaunchySharpCpp/StringConversions.h"

namespace LaunchySharpCpp
{
::CatItem CatItemConverter::toLaunchy(LaunchySharp::ICatItem^ catItem)
{
	::CatItem result;
	result.id = catItem->getID();
	result.fullPath = StringToQString( catItem->getFullPath() );
	result.shortName = StringToQString( catItem->getShortName() );
	result.icon = StringToQString( catItem->getIconPath() );
	result.lowName = StringToQString( catItem->getLowName() );
	result.usage = catItem->getUsage();
	return result;
}

LaunchySharpCpp::CatItem^ CatItemConverter::fromLaunchy(const ::CatItem& catItem)
{
	LaunchySharpCpp::CatItem^ result = gcnew LaunchySharpCpp::CatItem(
		QStringToString(catItem.fullPath),
		QStringToString(catItem.shortName),
		catItem.id,
		QStringToString(catItem.icon),
		catItem.usage, 
		QStringToString(catItem.lowName)
	);
	return result;
}

}