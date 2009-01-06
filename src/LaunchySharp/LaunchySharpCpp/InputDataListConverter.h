#pragma once

#include "Launchy/catalog.h"

namespace LaunchySharpCpp
{
	class InputDataFactory;

	class InputDataListConverter
	{
	public:
		InputDataListConverter(InputDataFactory& inputDataFactory);
		System::Collections::Generic::List<LaunchySharp::IInputData^>^
			fromLaunchy(QList<::InputData>& pInputDataList);

	private:
		InputDataFactory& m_inputDataFactory;
	};

}