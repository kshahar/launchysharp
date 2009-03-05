using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace GoYPlugin
{
    class WindowNameMatcher
    {
        public string m_windowNameToMatch = "";
        private bool m_isCaseSensitive = false;

        public string windowNameToMatch
        {
            get
            {
                return m_windowNameToMatch;
            }
            set
            {
                m_windowNameToMatch = value;
            }
        }

        public bool isCaseSensitive
        {
            get
            {
                return m_isCaseSensitive;
            }
            set
            {
                m_isCaseSensitive = value;
            }
        }

        public bool hasMatch(string windowName)
        {
            if (m_isCaseSensitive)
            {
                return hasMatch(windowName, m_windowNameToMatch);
            }
            else
            {
                return hasMatch(windowName.ToLower(),
                    m_windowNameToMatch.ToLower());
            }
        }

        private bool hasMatch(string windowName, string windowNameToMatch)
        {
            return windowName.IndexOf(windowNameToMatch) > -1;
        }
    }
}
