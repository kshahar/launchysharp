using System;
using System.Collections.Generic;
using ManagedWinapi.Windows;
using System.Drawing;
using System.Runtime.InteropServices;

namespace GoYPlugin
{
    class WindowsDictionary: Dictionary<string, IntPtr>
    {
    }

    class WindowController
    {
        private const int SW_RESTORE = 9;

        public WindowsDictionary topLevelWindows()
        {
            WindowsDictionary windowsDict = new WindowsDictionary();

            SystemWindow[] allTopLevelWindows = 
                SystemWindow.AllToplevelWindows;
            foreach (SystemWindow window in allTopLevelWindows)
            {
                if (window.HWnd == (IntPtr)0)
                    continue;
                if (window.Title == "")
                    continue;
                if (windowsDict.ContainsKey(window.Title))
                    continue;

                windowsDict.Add(window.Title, window.HWnd);
            }

            return windowsDict;
        }

        public void goToWindow(IntPtr hWnd)
        {
            if (isWindowRestored(hWnd))
            {
                ShowWindow(hWnd, SW_RESTORE);
            }
            else
            {
                BringWindowToTop(hWnd);
            }
            SetForegroundWindow(hWnd);
            SetActiveWindow(hWnd);
        }

        private bool isWindowRestored(IntPtr hWnd)
        {
            WINDOWPLACEMENT placement = new WINDOWPLACEMENT();
            placement.length = Marshal.SizeOf(placement);
            GetWindowPlacement(hWnd, ref placement);
            return placement.flags == SW_RESTORE;
        }

        #region WIN32
        [DllImport("user32.dll")]
        static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        [DllImport("user32.dll", SetLastError = true)]
        static extern bool BringWindowToTop(IntPtr hWnd);

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll")]
        static extern IntPtr SetActiveWindow(IntPtr hWnd);

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool GetWindowPlacement(IntPtr hWnd, ref WINDOWPLACEMENT lpwndpl);

        private struct WINDOWPLACEMENT
        {
            public int length;
            public int flags;
            public int showCmd;
            public System.Drawing.Point ptMinPosition;
            public System.Drawing.Point ptMaxPosition;
            public System.Drawing.Rectangle rcNormalPosition;
        }
        #endregion
    }
}
