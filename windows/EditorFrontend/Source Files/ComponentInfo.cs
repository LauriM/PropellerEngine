using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files
{
	public class ComponentInfo
	{
		public ComponentInfo(String componentName, String componentPath)
		{
			this.componentName = componentName;
			this.componentPath = componentPath;
		}

		public String componentName;
		public String componentPath;
	}
}
