using System;
using System.Collections.Generic;
using System.Windows.Forms;
using LaunchySharp;

namespace GoYPlugin
{
    public class GoYPlugin : IPlugin
    {
        private IPluginHost m_pluginHost = null;
        private ICatItemFactory m_catItemFactory = null;
        private ILaunchyPaths m_launchyPaths = null;
        private string m_name = "";
        private uint m_id = 0;
        private string m_iconPath = "";
        private uint m_labelHash = 0;
        private WindowController m_windowController = new WindowController();
        private WindowsDictionary m_topLevelWindows;

        public void init(LaunchySharp.IPluginHost pluginHost)
        {
            m_pluginHost = pluginHost;
            if (m_pluginHost == null) {
                return;
            }
            m_catItemFactory = m_pluginHost.catItemFactory();
            m_launchyPaths = m_pluginHost.launchyPaths();

            m_name = ("Go-Y#");
            m_id = m_pluginHost.hash(m_name);
            m_labelHash = m_id;
            m_iconPath = m_launchyPaths.getIconsPath() + "\\Go-Y#.ico";
        }

        public uint getID()
        {
            return m_id;
        }

        public string getName()
        {
            return m_name;
        }

        public string getIcon()
        {
            return m_iconPath;
        }

        public void getLabels(List<IInputData> inputDataList)
        {
            if (inputDataList.Count != 2)
            {
                return;
            }

            string lowerText = inputDataList[0].getText().ToLower();
            if (lowerText == "go" || lowerText == "focus")
            {
                inputDataList[0].setLabel(m_labelHash);
            }
        }

        public void getResults(List<IInputData> inputDataList, List<ICatItem> resultsList)
        {
            if (!inputDataList[0].hasLabel(m_labelHash))
            {
                return;
            }

            string windowNameToMatch = inputDataList[1].getText().ToLower();
		    if (windowNameToMatch == "") 
            {
                return;
            }

            m_topLevelWindows = m_windowController.topLevelWindows(); 

            foreach (string windowName in m_topLevelWindows.Keys) {
                string windowNameLower = windowName.ToLower();
                if (windowNameLower.IndexOf(windowNameToMatch) > -1)
                {
                    ICatItem result = m_catItemFactory.createCatItem(
                        windowName + ".go-y", windowName, getID(), getIcon());
                    resultsList.Add(result);
                }
            }
        }

        public void getCatalog(List<ICatItem> catalogItems)
        {
            catalogItems.Add( m_catItemFactory.createCatItem(
                "Go.go-y", "Go", getID(), getIcon() ) );
            catalogItems.Add( m_catItemFactory.createCatItem(
                "Focus.go-y", "Focus", getID(), getIcon() ) );
        }

        public void launchItem(List<IInputData> inputDataList, ICatItem item)
        {
            ICatItem catItem =
                inputDataList[inputDataList.Count - 1].getTopResult();
            try
            {
                IntPtr hWnd = m_topLevelWindows[catItem.getShortName()];
                m_windowController.goToWindow(hWnd);
            }
            catch (Exception )
            {
            }
        }
    }
}
