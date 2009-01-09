using System;
using System.Collections.Generic;
namespace LaunchySharp
{
    /// <summary>
    /// Interface for creating a Launchy plugin using the .NET framework.
    /// </summary>
	public interface IPlugin
	{
        /// <summary>
        /// This function informs the plugin that it’s being loaded.
        /// This is a good time to do any initialization work, including
        /// creating the plugin ID hash value.
        /// </summary>
        /// <param name="pluginHost"></param>
		void init(IPluginHost pluginHost);

        /// <summary>
        /// Asks the Plugin for its ID Number.
        /// </summary>
        /// <remarks>
        /// Launchy needs an unsigned int identification value for each loaded 
        /// plugin. You supply your own here. Typically, this is the result of 
        /// hashing a string, as shown in the example below.
        /// <example>
        /// <code>
        /// uint getID()
        /// {
        ///     return m_pluginHost.hash("MyPluginName");
        /// }
        /// </code>
        /// </example>
        /// </remarks>
        /// <returns></returns>
		uint getID();

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
		string getName();

        /// <summary>
        /// 
        /// </summary>
        /// <param name="inputDataList"></param>
		void getLabels(List<IInputData> inputDataList);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="inputDataList"></param>
        /// <param name="resultsList"></param>
		void getResults(List<IInputData> inputDataList, List<ICatItem> resultsList);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="catalogItems"></param>
		void getCatalog(List<ICatItem> catalogItems);

        /// <summary>
        /// 
        /// </summary>
        /// <param name="inputDataList"></param>
        /// <param name="item"></param>
		void launchItem(List<IInputData> inputDataList, ICatItem item);
		
        // Currently not implemented
		//void LaunchySharpPluginWrapper::doDialog(QWidget* parent, QWidget**);
		//void LaunchySharpPluginWrapper::endDialog(bool accept);
		//void LaunchySharpPluginWrapper::launchyShow();
		//void LaunchySharpPluginWrapper::launchyHide();
	}
	
    /// <summary>
    /// 
    /// </summary>
	public interface IPluginHost
	{
        /// <summary>
        /// Returns an object that creates CatItem objects.
        /// </summary>
        /// <returns></returns>
		ICatItemFactory catItemFactory();
		
        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
		ILaunchyPaths launchyPaths();
		
        /// <summary>
        /// Computes a value of a string using the implmentation as Launchy.
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
		uint hash(string str);
	}
	
    /// <summary>
    /// 
    /// </summary>
	public interface ICatItem
	{	
		/// <summary>
        /// The full path of the file to execute
		/// </summary>
        /// <returns></returns>
		string getFullPath();
		
        /// <summary>
        /// The abbreviated name of the indexed item.
        /// </summary>
        /// <returns></returns>
		string getShortName();

        /// <summary>
        /// The lowercase name of the indexed item.
        /// </summary>
        /// <returns></returns>
		string getLowName();

        /// <summary>
        /// A path to an icon for the item.
        /// </summary>
        /// <returns></returns>
		string getIconPath();

        /// <summary>
        /// How many times this item has been called by the user.
        /// </summary>
        /// <returns></returns>
		int getUsage();

        /// <summary>
        /// The plugin id of the creator of this CatItem (0 for Launchy itself).
        /// </summary>
        /// <returns></returns>
		uint getID();
	}
	
    /// <summary>
    /// 
    /// </summary>
	public interface IInputData
	{
		// Get the labels applied to this query segment.
		// QSet< uint > getLabels () 
		
		/// <summary>
        /// Apply a label to this query segment.
		/// </summary>
		/// <param name="label"></param>
		void setLabel(uint label);
		
        /// <summary>
        /// Check if it has the given label applied to it.
        /// </summary>
        /// <param name="label"></param>
        /// <returns></returns>
		bool hasLabel(uint label);

        /// <summary>
        /// Set the id of this query.
        /// </summary>
        /// <param name="id"></param>
		void setID(uint id);
		
        /// <summary>
        /// Returns the current owner id of the query.
        /// </summary>
        /// <returns></returns>
		uint getID();
		
		/// <summary>
        /// Get the text of the query segment.
		/// </summary>
		/// <returns></returns>
		string getText();
		
		/// <summary>
        /// Set the text of the query segment.
		/// </summary>
		/// <param name="text"></param>
		void setText(string text);
		
		/// <summary>
        /// Get a pointer to the best catalog match for this segment of the query.
		/// </summary>
		/// <returns></returns>
		ICatItem getTopResult();
		
		/// <summary>
        /// Change the best catalog match for this segment.
		/// </summary>
		/// <param name="catItem"></param>
		void setTopResult(ICatItem catItem);
	}
	
    /// <summary>
    /// 
    /// </summary>
	public interface ICatItemFactory
	{
        /// <summary>
        /// 
        /// </summary>
        /// <param name="fullPath"></param>
        /// <param name="shortName"></param>
        /// <param name="id"></param>
        /// <param name="iconPath"></param>
        /// <returns></returns>
		ICatItem createCatItem(string fullPath, string shortName, uint id, 
			string iconPath);
	}
	
    /// <summary>
    /// 
    /// </summary>
	public interface ILaunchyPaths
	{
		/// <summary>
        /// Usually C:\Program Files\Launchy.
		/// </summary>
		/// <returns></returns>
		string getLaunchyPath();
		
		/// <summary>
        /// Usually C:\Program Files\Launchy\plugins\icons.
		/// </summary>
		/// <returns></returns>
		string getIconsPath();
	}
}
