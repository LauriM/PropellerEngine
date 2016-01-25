using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.Instances.Statistics
{
	class StatsInstance : NativeInstance
	{
		private IntPtr targetInstance;
		private Stats.StatsView statsView;

		public StatsInstance(IntPtr targetInstance, Stats.StatsView statsView)
			: base("StatsView")
		{
			this.targetInstance = targetInstance;
			this.statsView = statsView;

			registerEvent("addPoint", statsView, typeof(Stats.StatsView).GetMethod("addPoint"));

			setTargetInstance(targetInstance);
		}

		private void setTargetInstance(IntPtr targetInstance)
		{
			call("setTargetInstance", targetInstance);
		}

		public override void update()
		{
			if (statsView.isClosed)
				instanceShutdown();

			call("update");
		}
	}
}
