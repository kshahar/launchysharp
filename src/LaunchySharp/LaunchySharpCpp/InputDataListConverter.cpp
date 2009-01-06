#include "Precompiled.h"
#include "LaunchySharpCpp/InputDataListConverter.h"
#include "LaunchySharpCpp/InputData.h"
#include "LaunchySharpCpp/InputDataFactory.h"

namespace LaunchySharpCpp
{

using namespace System::Collections::Generic;

InputDataListConverter::InputDataListConverter(
	InputDataFactory& inputDataFactory)
: m_inputDataFactory(inputDataFactory)
{
}

List<LaunchySharp::IInputData^>^ InputDataListConverter::fromLaunchy(
	QList<::InputData>& launchyInputDataList)
{
	List<LaunchySharp::IInputData^>^ inputDataList = 
		gcnew List<LaunchySharp::IInputData^>;

	QList<::InputData>::Iterator it = launchyInputDataList.begin();
	QList<::InputData>::Iterator itEnd = launchyInputDataList.end();
	for ( ; it != itEnd; ++it ) {
		LaunchySharp::IInputData^ inputData = 
			m_inputDataFactory.createInputData(*it);
		inputDataList->Add(inputData);
	}

	return inputDataList;
}

}