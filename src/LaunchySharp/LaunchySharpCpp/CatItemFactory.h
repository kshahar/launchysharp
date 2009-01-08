#pragma once

namespace LaunchySharpCpp
{
	ref class CatItemFactory: public LaunchySharp::ICatItemFactory 
	{
	public:
		virtual LaunchySharp::ICatItem^ createCatItem(System::String^ fullPath, 
			System::String^ shortName, unsigned int id, System::String^ iconPath);
	};

}