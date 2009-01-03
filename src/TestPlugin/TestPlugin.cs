using System;
using System.Collections.Generic;
namespace LaunchySharp
{
	public class TestPlugin: IPlugin
	{
		public void init()
		{
		}
		public int getID()
		{
			return 8844233;
		}
		public string getName()
		{
			return "TestPlugin";
		}
		public string getIcon()
		{
			return "";
		}
		public void getLabels(List<IInputData> inputDataList)
		{
		}
	}
}
