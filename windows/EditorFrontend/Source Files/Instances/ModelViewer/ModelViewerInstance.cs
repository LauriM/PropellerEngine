using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.Instances.ModelViewer
{
	class ModelViewerInstance : NativeInstance
	{
		private ModelViewerView view { get; set; }

		public ModelViewerInstance(ModelViewerView v, String modelName)
			: base("ModelViewer")
		{
			view = v;

			v.setModelViewerInstance(this);

			call("initModelViewer",  modelName, view.renderPanel.Handle);
			flush();
		}

		public override void update()
		{
			call("update");
		}


		internal void keyDown(int p)
		{
			call("keyDown", p);
		}

		internal void keyUp(int p)
		{
			call("keyUp", p);
		}

		internal void mouseDeltaInput(int p1, int p2)
		{
			call("mouseDeltaInput", (float)p1, (float)p2);
		}

		internal void toggleWireframe()
		{
			call("toggleWireframe");
		}

		internal void toggleGrid()
		{
			call("toggleGrid");
		}
	}
}
