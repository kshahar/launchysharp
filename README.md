Launchy#
====================

Launchy# is an extension to [Launchy][launchy]'s plugin system, that allows developing Launchy plugins in .NET languages (C#, VB.NET, etc.).

Launchy# contains two main parts:

  - A .NET assembly that provides the plugin API and contains all relevant interfaces.
  - A Launchy plugin that acts as a proxy: loads the .NET plugins and forwards calls from Launchy to them.

When Launchy starts, Launchy# searches for .NET assemblies (DLL files) in the 'plugins' directory that implement the required interfaces. The .NET plugins are loaded and wrapped, so that Launchy treats them as regular Launchy plugins.

Downloads
-------
  - [Launchy#-1.1.1-Bin.zip][launchy#bin] - contains the basic Launchy# distribution, including the proxy plugin, API assembly and documentation. Extract this file in the main Launchy directory (e.g. C:\Program Files\Launchy).
  - [Go-Y#-1.1.0-Bin.zip][go-y] - a full-fledged plugin that allows switching to an opened window. See the attached readme file for more details.

Links
-------
  - [Project downloads][Downloads] (SourceForge)
  - [Forum][Forum] (SourceForge)

Community plugins
-------
Community plugins that use Launchy#:

  - [Launchy2Skype][Launchy2Skype] - use Launchy to open Skype chat windows with your friends.
  - [CSVy][CSVy] - A Launchy# plugin to access CSV files directly in Launchy.
  - [launchy-translate][launchy-translate] - translation plugin (uses Lingvo).

Your first plugin
-------
Before attempting to develop your first plugin you can consult with the following:

  - API documentation that comes with Launchy# (LaunchySharpAPI.chm).
  - SimplePlugin - a simple plugin that echos the user query. 
  - Go-Y# (under "plugins") - a full-fledged plugin that allows switching to an opened window.

The source code for both of the plugins is available under the "plugins" directory.

Requirements
-------
Launchy# requires Launchy 2.5 and .NET framework 2.0 and above.

License
-------
  - Launchy# is licensed under the terms of the GNU General Public License version 2.0 (GPLv2).
  - The Launchy# .NET plugin API is licensed under the terms of the GNU Lesser General Public License version 2.0 (LGPLv2).

  [launchy]: http://launchy.net
  [launchy#bin]: http://sourceforge.net/projects/launchysharp/files/Launchy%23/1.1.1/LaunchySharp-1.1.1-Bin.zip/download
  [go-y]: http://sourceforge.net/projects/launchysharp/files/Go-Y%23/1.1.0/Go-YSharp-1.1.0-Bin.zip/download
  [Launchy2Skype]: http://home.spurgius.com/launchy2skype
  [CSVy]: http://code.google.com/p/csvy/
  [launchy-translate]: http://code.google.com/p/launchy-translate/
  [Downloads]: http://sourceforge.net/projects/launchysharp/files/
  [Forum]: https://sourceforge.net/p/launchysharp/discussion/903447
