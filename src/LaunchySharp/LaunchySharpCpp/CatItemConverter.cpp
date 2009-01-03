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
	result.lowName = StringToQString( catItem->getLowName() );
	result.usage = catItem->getUsage();
	return result;
}

LaunchySharpCpp::CatItem^ CatItemConverter::fromLaunchy(::CatItem& catItem)
{
	LaunchySharpCpp::CatItem^ result = gcnew LaunchySharpCpp::CatItem();
	return result;
}

}