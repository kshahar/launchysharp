/*
Launchy#: .NET bindings for Launchy plugins.
Copyright (C) 2009  Shahar Kosti

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

using System;
using System.Collections.Generic;

// The LaunchySharp namespace contains the public API of Launchy#.
namespace LaunchySharp
{
    /// <summary>
    /// An interface for creating a Launchy plugin using the .NET framework.
    /// Launchy# will load all DLLs that have a public class which derives from
    /// IPlugin.
    /// </summary>
    /// <remarks>
    /// Some simple guidelines for writing plugins:
    /// <list type="bullet">
    /// <item>The main purpose of most Launchy plugins is to add items of
    /// some type the main catalog.</item>
    /// <item>The init, getID and getName should be implmeneted by all 
    /// plugins. The other methods should be implemented according to the 
    /// plugin purpose</item>
    /// </list>
    /// </remarks>
    public interface IPlugin
    {
        /// <summary>
        /// This function informs the plugin that it’s being loaded.
        /// This is a good time to do any initialization work, including
        /// creating the plugin ID hash value.
        /// </summary>
        /// <param name="pluginHost">an object for the plugin to interact with 
        /// the main program.</param>
        /// <example>
        /// <code source="DocumentationPlugin.cs" region="init"></code>
        /// </example>
        /// <seealso cref="IPluginHost"/>
        void init(IPluginHost pluginHost);

        /// <summary>
        /// Asks the Plugin for its ID number.
        /// </summary>
        /// <remarks>
        /// Launchy needs an unsigned int identification value for each loaded 
        /// plugin. You supply your own here. Typically, this is the result of 
        /// hashing a string, as shown in the example below.
        /// </remarks>
        /// <example>
        /// <code source="DocumentationPlugin.cs" region="getID"></code>
        /// </example>
        /// <returns>The plugin ID number</returns>
        uint getID();

        /// <summary>
        /// Asks the plugin for its string name.
        /// </summary>
        /// <returns>The plugin name</returns>
        string getName();

        /// <summary>
        /// Asks the plugin if it would like to apply a label to the current 
        /// search query.
        /// </summary>
        /// <remarks>
        /// It is sometimes useful to label user queries with plugin-defined 
        /// tags. For instance, the weby plugin will tag input that contains 
        /// "www" or ".com" or ".net" with the hash value of the string 
        /// "HASH_WEBSITE". Then, other plugins that see the query can know 
        /// that the current search is for a website.
        /// </remarks>
        /// <param name="inputDataList">User's search query</param>
        /// <example>
        /// <code source="DocumentationPlugin.cs" region="getLabels"></code>
        /// </example>
        /// <seealso cref="IInputData"/>
        void getLabels(List<IInputData> inputDataList);

        /// <summary>
        /// Asks the plugin for any results to a query.
        /// </summary>
        /// <remarks>
        /// If your plugin returns catalog results on the fly to a query (e.g. 
        /// a website query for weby or a calculator result), then this is the 
        /// place to do so. The existing results are stored in a ResultsList 
        /// object, which is a CatItem‘s (short for Catalog Items) list. 
        /// You can append your own results to it.
        /// </remarks>
        /// <param name="inputDataList">User's search query</param>
        /// <param name="resultsList">A list of results for this query,
        /// you can add your own if relevant.</param>
        /// <seealso cref="IInputData"/>
        /// <seealso cref="ICatItem"/>
        void getResults(List<IInputData> inputDataList, List<ICatItem> resultsList);

        /// <summary>
        /// Asks the plugin for a static catalog to be added to the primary 
        /// catalog. Some plugins will add permanent entries to Launchy's 
        /// primary catalog (until the catalog is rebuilt).
        /// </summary>
        /// <param name="catalogItems">An object to append your new entries to 
        /// (these will be copied over to the primary catalog).</param>
        /// <seealso cref="ICatItem"/>
        void getCatalog(List<ICatItem> catalogItems);

        /// <summary>
        /// This method instructs the plugin that one of its own catalog 
        /// items was selected by the user and should now be executed.
        /// </summary>
        /// <remarks>
        /// If the plugin adds items to the catalog via getResults() or 
        /// getCatalog(), and one of those items is selected by the user, 
        /// then it is up to the plugin to execute it when the user presses 
        /// "enter". This is where you perform the action. 
        /// </remarks>
        /// <param name="inputDataList">The user's query</param>
        /// <param name="item">The user selected catalog item</param>
        /// <seealso cref="IInputData"/>
        /// <seealso cref="ICatItem"/>
        void launchItem(List<IInputData> inputDataList, ICatItem item);

        /// <summary>
        /// Asks the plugin if it has a dialog to display in the options menu.
        /// </summary>
        bool hasDialog();

        /// <summary>
        /// Asks the plugin to create an options window for the Launchy 
        /// "Options->Plugins" tab, and return a handle (HWND) to it.
        /// </summary>
        /// <remarks>
        /// This function is called only if hasDialog() returns true.
        /// </remarks>
        /// <returns>The configuration window handle (HWND).</returns>
        IntPtr doDialog();

        /// <summary>
        /// Informs the plugin that it should close its dialog.
        /// </summary>
        /// <param name="acceptedByUser">
        /// True if the plugin should accept changes made by the user while
        /// the dialog was open.
        /// </param>
        void endDialog(bool acceptedByUser);

        /// <summary>
        /// Informs the plugin that Launchy is now visible on the screen.
        /// </summary>
        void launchyShow();

        /// <summary>
        /// Informs the plugin that Launchy is no longer visible on the screen.
        /// </summary>
        void launchyHide();

        /// <summary>
        /// This message informs Launchy of what directory the plugin was loaded from.
        /// This can be helpful in determining where the icon should be loaded from.
        ///</summary>
        void setPath(string pluginPath);
    }
    
    /// <summary>
    /// Interface for the plugin to interact with the main program.
    /// </summary>
    public interface IPluginHost
    {
        /// <summary>
        /// Returns an object that creates CatItem objects.
        /// </summary>
        /// <returns>An object that creates CatItem objects</returns>
        /// <see cref="ICatItemFactory"/>
        ICatItemFactory catItemFactory();
        
        /// <summary>
        /// Returns an object that contains information about file system
        /// paths.
        /// </summary>
        /// <returns>An object that contains information about file system
        /// paths.</returns>
        /// <seealso cref="ILaunchyPaths"/>
        ILaunchyPaths launchyPaths();
        
        /// <summary>
        /// Computes a value of a string using the same implmentation as 
        /// Launchy.
        /// </summary>
        /// <param name="str">The string to hash.</param>
        /// <remarks>
        /// Internally, this function uses the Qt function qHash(), which is
        /// the same function used by Launchy.
        /// </remarks>
        /// <returns>An integer which represents the string.</returns>
        uint hash(string str);
    }
    
    /// <summary>
    /// Interface for a single item in the index.
    /// </summary>
    public interface ICatItem
    {    
        /// <summary>
        /// Returns the full path of the file to execute.
        /// </summary>
        /// <returns>The full path of the file to execute.</returns>
        string getFullPath();
        
        /// <summary>
        /// Returns the abbreviated name of the indexed item.
        /// </summary>
        /// <returns>The abbreviated name of the indexed item.</returns>
        string getShortName();

        /// <summary>
        /// The lowercase name of the indexed item.
        /// </summary>
        /// <returns>The lowercase name of the indexed item.</returns>
        string getLowName();

        /// <summary>
        /// Returns the path to icon file for the item.
        /// </summary>
        /// <returns>The path to icon file for the item.</returns>
        string getIconPath();

        /// <summary>
        /// Returns how many times this item has been called by the user.
        /// </summary>
        /// <returns>how many times this item has been called by the user.
        /// </returns>
        int getUsage();

        /// <summary>
        /// Returns the plugin id of the creator of this CatItem (0 for Launchy 
        /// itself).
        /// </summary>
        /// <returns>the plugin id of the creator of this CatItem 
        /// (0 for Launchy itself).</returns>
        uint getID();
    }
    
    /// <summary>
    /// Interace for a class that stores one segment (between tabs) of a user's 
    /// query. The query is typically represented by a List of IInputData, 
    /// and each element of the list represents a segment of the query.
    /// </summary>
    /// <example>
    /// For the user query "google |TAB| this is my search", 2 InputData 
    /// objects are created. One for "google" and one for "this is my search".
    /// </example>
    public interface IInputData
    {
        // Currently not implemented:
        // Get the labels applied to this query segment.
        // QSet< uint > getLabels () 
        
        /// <summary>
        /// Apply a label to this query segment.
        /// </summary>
        /// <param name="label">Identifier for this query.</param>
        void setLabel(uint label);
        
        /// <summary>
        /// Check if it has the given label applied to it.
        /// </summary>
        /// <param name="label">The label ID to check for.</param>
        /// <returns>True if label exists for this query, or false otherwise.
        /// </returns>
        bool hasLabel(uint label);

        /// <summary>
        /// Set the id of this query.
        /// </summary>
        /// <param name="id">Identifier for this query.</param>
        void setID(uint id);
        
        /// <summary>
        /// Returns the current owner id of the query.
        /// </summary>
        /// <returns>The current owner id of the query</returns>
        uint getID();
        
        /// <summary>
        /// Get the text of the query segment.
        /// </summary>
        /// <returns>The text of the query segment</returns>
        string getText();

        /// <summary>
        /// Set the text of the query segment.
        /// </summary>
        /// <param name="text">The text of the query segment</param>
        void setText(string text);
        
        /// <summary>
        /// Get a pointer to the best catalog match for this segment of the 
        /// query.
        /// </summary>
        /// <returns>The best catalog match for this segment of the query.
        /// </returns>
        ICatItem getTopResult();

        /// <summary>
        /// Change the best catalog match for this segment.
        /// </summary>
        /// <param name="catItem">The best catalog match for this segment.
        /// </param>
        void setTopResult(ICatItem catItem);
    }
    
    /// <summary>
    /// Interface for classes that create ICatItem objects.
    /// </summary>
    /// <seealso cref="ICatItem"/>
    public interface ICatItemFactory
    {
        /// <summary>
        /// Creates a new CatItem using 4 parameters.
        /// </summary>
        /// <param name="fullPath">Full path of the file to execute.</param>
        /// <param name="shortName">Abbreviated name of the indexed item.</param>
        /// <param name="id">Owner ID of the CatItem, should be the result the
        /// plugin ID.</param>
        /// <param name="iconPath">Icon path</param>
        /// <returns>The new CatItem, as a ICatItem reference</returns>
        ICatItem createCatItem(string fullPath, string shortName, uint id, 
            string iconPath);

        /// <summary>
        /// Creates a new CatItem using 5 parameters.
        /// </summary>
        /// <param name="fullPath">Full path of the file to execute.</param>
        /// <param name="shortName">Abbreviated name of the indexed item.</param>
        /// <param name="id">Owner ID of the CatItem, should be the result the
        /// plugin ID.</param>
        /// <param name="iconPath">Icon path</param>
        /// <param name="usage">Usage count</param>
        /// <returns>The new CatItem, as a ICatItem reference</returns>
        ICatItem createCatItem(string fullPath, string shortName, uint id,
             string iconPath, uint usage);
    }
    
    /// <summary>
    /// Returns some file system paths for common directories.
    /// </summary>
    public interface ILaunchyPaths
    {
        /// <summary>
        /// Returns the path where Launchy.exe resides. 
        /// Usually this is C:\Program Files\Launchy.
        /// </summary>
        /// <returns>The path where Launchy.exe resides.</returns>
        string getLaunchyPath();
        
        /// <summary>
        /// Returns the icons directory for Launchy plugins.
        /// Usually this is C:\Program Files\Launchy\plugins\icons.
        /// </summary>
        /// <returns>The icons directory for Launchy plugins.</returns>
        string getIconsPath();

        /// <summary>
        /// Returns the Launchy configuration file directory, where 
        /// Launchy.ini resides. Usually this is %APPDATA%\Launchy.
        /// </summary>
        /// <returns>The Launchy configuration directory.</returns>
        string getConfigPath();
    }
}
