#pragma once

#include "Launchy/Catalog.h"

namespace LaunchySharpCpp
{
	class CatItemConverter;

	ref class InputData: LaunchySharp::IInputData
	{
	public:
		InputData(::InputData& inputData, CatItemConverter& catItemConverter);

		// Apply a label to this query segment.
		virtual void setLabel(unsigned int label);
		
		// Check if it has the given label applied to it.
		virtual bool hasLabel(unsigned int label);
		
		// Set the id of this query.
		virtual void setID(unsigned int id);
		
		// Returns the current owner id of the query.
		virtual unsigned int getID();
		
		// Get the text of the query segment.
		virtual System::String^ getText();
		
		// Set the text of the query segment.
		virtual void setText(System::String^ text);
		
		// Get a pointer to the best catalog match for this segment of the query.
		virtual LaunchySharp::ICatItem^ getTopResult();
		
		// Change the best catalog match for this segment.
		virtual void setTopResult(LaunchySharp::ICatItem^ catItem);

	private:
		::InputData& m_inputData;
		CatItemConverter& m_catItemConverter;
	};
}