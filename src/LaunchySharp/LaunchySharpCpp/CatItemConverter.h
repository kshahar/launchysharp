#pragma once

#include "Launchy/catalog.h"
#include "LaunchySharpCpp/CatItem.h"

namespace LaunchySharpCpp
{
	class CatItemConverter
	{
	public:
		::CatItem toLaunchy(LaunchySharp::ICatItem^ catItem);
		LaunchySharpCpp::CatItem^ fromLaunchy(const ::CatItem& catItem);
	};
};