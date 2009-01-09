using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace LaunchySharp
{
	public class SimplePlugin: IPlugin
	{
		private LaunchySharp.IPluginHost m_pluginHost = null;
		private LaunchySharp.ICatItemFactory m_catItemFactory = null;
		private uint m_id = 0;
		private string m_name = "SimplePlugin#";
	
		public void init(LaunchySharp.IPluginHost pluginHost)
		{
			m_pluginHost = pluginHost;
			if (m_pluginHost != null) {
				m_catItemFactory = m_pluginHost.catItemFactory();
			}
			m_id = m_pluginHost.hash(m_name);
		}
		
		public uint getID()
		{
			return m_id;
		}
		
		public string getName()
		{
			return m_name;
		}
		
		public void getLabels(List<IInputData> inputDataList)
		{
		}
		
		public void getResults(List<IInputData> inputDataList, List<ICatItem> resultsList)
		{
			((IInputData)null).getText();
			string text = inputDataList[0].getText();
			resultsList.Add( m_catItemFactory.createCatItem( 
				text, "SimplePlugin: " + text, getID(), getName()) );
		}
		
		public void getCatalog(List<ICatItem> catalogItems)
		{
		}
		
		public void launchItem(List<IInputData> inputDataList, ICatItem item)
		{
			ICatItem catItem = 
				inputDataList[inputDataList.Count-1].getTopResult();
			MessageBox.Show("I was asked to launch: " + item.getFullPath());
		}
	}
}
