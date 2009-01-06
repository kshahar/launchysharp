#pragma once

#include "Launchy/catalog.h"
#include "LaunchySharpCpp/CatItemConverter.h"

namespace LaunchySharpCpp
{
	class CatItemConverter;
	class InputDataFactory
	{
	public:
		LaunchySharp::IInputData^ createInputData(::InputData& inputData);
	private:
		CatItemConverter m_catItemConverter;
	};
}
