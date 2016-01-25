using Editor.Source_Files;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor
{
	// Class to manage engines component information
	// Names, source paths, etc
	public class ComponentInfoManager
	{
		private List<ComponentInfo> componentInfoList;

		public ComponentInfoManager()
		{
			componentInfoList = new List<ComponentInfo>();
		}

		public void addComponentInfo(ComponentInfo info)
		{
			componentInfoList.Add(info);
		}

		public List<ComponentInfo> getComponentInfoList()
		{
			return componentInfoList;
		}

		public ComponentInfo getComponentInfoByName(string name)
		{
			for(int i = 0; i < componentInfoList.Count; ++i)
			{
				if (componentInfoList[i].componentName == name)
					return componentInfoList[i];
			}

			return null;
		}

		public ComponentInfo getComponentInfoByIndex(int id)
		{
			return componentInfoList[id];
		}

		internal int count()
		{
			return componentInfoList.Count;
		}
	}
}
