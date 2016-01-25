using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.Instances
{
	class GameInstance : NativeInstance
	{
		public GameInstance()
			: base("GameView")
		{
			registerEvent("kill", this, typeof(GameInstance).GetMethod("kill"));
		}

		public override void update()
		{
			call("update");
		}

		// Kill instance, called from the C++ side
		public void kill()
		{
			instanceShutdown();
		}

		internal void startup(IntPtr stream)
		{
			call("startup", stream);
		}
	}
}
