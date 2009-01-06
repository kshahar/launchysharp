#include "Precompiled.h"
#include "LaunchySharpCpp/InputDataFactory.h"
#include "LaunchySharpCpp/InputData.h"

namespace LaunchySharpCpp
{

LaunchySharp::IInputData^ InputDataFactory::createInputData(::InputData& inputData)
{
	return gcnew LaunchySharpCpp::InputData(inputData, m_catItemConverter);
}

}
