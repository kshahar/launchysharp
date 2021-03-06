#include "Precompiled.h"
#include "LaunchySharpCpp/CatItemFactory.h"
#include "LaunchySharpCpp/CatItem.h"

namespace LaunchySharpCpp
{

LaunchySharp::ICatItem^ CatItemFactory::createCatItem(
	System::String^ fullPath, System::String^ shortName, 
	unsigned int id, System::String^ iconPath)
{
	return gcnew LaunchySharpCpp::CatItem( fullPath, shortName, id, iconPath );
}

LaunchySharp::ICatItem^ CatItemFactory::createCatItem(
	System::String^ fullPath, System::String^ shortName, 
	unsigned int id, System::String^ iconPath, unsigned int usage)
{
	return gcnew LaunchySharpCpp::CatItem( fullPath, shortName, id, iconPath, 
		usage );
}

}