using System;
using System.Collections.Generic;
namespace LaunchySharp
{
	public interface IPlugin
	{
		void init(IPluginHost pluginHost);
		uint getID();
		string getName();
		void getLabels(List<IInputData> inputDataList);
		void getResults(List<IInputData> inputDataList, List<ICatItem> resultsList);
		void getCatalog(List<ICatItem> catalogItems);
		void launchItem(List<IInputData> inputDataList, ICatItem item);
		
		//void LaunchySharpPluginWrapper::doDialog(QWidget* parent, QWidget**);
		//void LaunchySharpPluginWrapper::endDialog(bool accept);
		//void LaunchySharpPluginWrapper::launchyShow();
		//void LaunchySharpPluginWrapper::launchyHide();
	}
	
	public interface IPluginHost
	{
		ICatItemFactory catItemFactory();
	}

	public interface ICatItem
	{	
		/// The full path of the file to execute
		string getFullPath();
		
		/// The abbreviated name of the indexed item.
		string getShortName();
		
		/// The lowercase name of the indexed item.
		string getLowName();
		
		/// A path to an icon for the item.
		string getIconPath();
		
		/// How many times this item has been called by the user.
		int getUsage();
		
		/// The plugin id of the creator of this CatItem (0 for Launchy itself).
		uint getID();
	}
	
	public interface ICatItemFactory
	{
		ICatItem createCatItem(string fullPath, string shortName, int id, 
			string iconPath);
	}
	
	public interface IInputData
	{
		// Get the labels applied to this query segment.
		// QSet< uint > getLabels () 
		
		// Apply a label to this query segment.
		void setLabel(uint label);
		
		// Check if it has the given label applied to it.
		bool hasLabel(uint label);
		
		// Set the id of this query.
		void setID(uint id);
		
		// Returns the current owner id of the query.
		uint getID();
		
		// Get the text of the query segment.
		string getText();
		
		// Set the text of the query segment.
		void setText(string text);
		
		// Get a pointer to the best catalog match for this segment of the query.
		ICatItem getTopResult();
		
		// Change the best catalog match for this segment.
		void setTopResult(ICatItem catItem);
	}
}
