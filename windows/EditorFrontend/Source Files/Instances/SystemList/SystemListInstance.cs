using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.Instances.SystemList
{
	class SystemListInstance : NativeInstance
	{
		private IntPtr targetInstance;
		private SystemListView systemListView;

		public SystemListInstance(IntPtr targetInstance, SystemListView systemListView)
			: base("SystemListView")
		{
			this.targetInstance = targetInstance;
			this.systemListView = systemListView;

			registerEvent("addSystem", systemListView, typeof(SystemListView).GetMethod("addSystem"));

			setTargetInstance(targetInstance);

			refreshList();
		}

		private void setTargetInstance(IntPtr targetInstance)
		{
			call("setTargetInstance", targetInstance);
		}

		public void refreshList()
		{
			call("refresh");
			flush();
			flush();
		}

	}
}
