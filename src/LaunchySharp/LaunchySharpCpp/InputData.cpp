#include "LaunchySharpCpp/InputData.h"
#include "LaunchySharpCpp/StringConversions.h"
#include "LaunchySharpCpp/CatItemConverter.h"
#include "LaunchySharpCpp/CatItem.h"

namespace LaunchySharpCpp
{

InputData::InputData(::InputData& inputData, CatItemConverter& catItemConverter)
: m_inputData(inputData),
  m_catItemConverter(catItemConverter)
{
}

void InputData::setLabel(unsigned int label)
{
	m_inputData.setLabel(label);
}

bool InputData::hasLabel(unsigned int label)
{
	return m_inputData.hasLabel(label);
}

void InputData::setID(unsigned int id)
{
}

void InputData::getID()
{
}

System::String^ InputData::getText()
{
	return QStringToString( m_inputData.getText() );
}

void InputData::setText(System::String^ text)
{
	m_inputData.setText( StringToQString(text) );
}

LaunchySharp::ICatItem^ InputData::getTopResult()
{
	::CatItem& topResult = m_inputData.getTopResult();
	return m_catItemConverter.fromLaunchy( topResult );
}

void InputData::setTopResult(LaunchySharp::ICatItem^ catItem)
{
	m_inputData.setTopResult( m_catItemConverter.toLaunchy(catItem) );
}

};