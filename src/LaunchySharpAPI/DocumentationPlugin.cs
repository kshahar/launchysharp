namespace LaunchySharp
{
    public class DocumentationPlugin: IPlugin
    {
        #region init
        public void init(IPluginHost pluginHost)
        {
            m_pluginHost = pluginHost;
            if (m_pluginHost == null) {
                return;
            }
            m_catItemFactory = m_pluginHost.catItemFactory();
            m_launchyPaths = m_pluginHost.launchyPaths();

            m_name = ("TestPlugin#");
            m_id = m_pluginHost.hash(m_name);
            m_iconPath = m_launchyPaths.getIconsPath() + "\\test.ico";
        }
        #endregion
        
        #region getID
        uint getID()
        {
            return m_pluginHost.hash("MyPluginName");
        }
        #endregion
        
        #region getLabels
        public void getLabels(List<IInputData> inputDataList)
        {
            if (inputDataList.Count >= 0)
            {
                // Apply a "website" label if we think it's a website
                IInputData lastInputData = 
                    inputDataList[inputDataList.Count - 1];

                string text = lastInputData.getText();
                if (text.IndexOf("http://") > -1)
                {
                    lastInputData.setLabel(HASH_WEBSITE);
                }
                else if (text.IndexOf("https://") > -1)
                {
                    lastInputData.setLabel(HASH_WEBSITE);
                }
                else if (text.IndexOf(".com") > -1)
                {
                    lastInputData.setLabel(HASH_WEBSITE);
                }
                else if (text.IndexOf(".net") > -1)
                {
                    lastInputData.setLabel(HASH_WEBSITE);
                }
                else if (text.IndexOf(".org") > -1)
                {
                    lastInputData.setLabel(HASH_WEBSITE);
                }
                else if (text.IndexOf("www.") > -1)
                {
                    lastInputData.setLabel(HASH_WEBSITE);
                }
            }
        }
        #endregion
    }
}