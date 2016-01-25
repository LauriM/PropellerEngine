using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.Instances.ParticleEditor
{
	public class ParticleEditorInstance : NativeInstance
	{
		private ParticleEditorView view { get; set; }

		//TODO: Closing effects instance not implemented!

		public ParticleEditorInstance(ParticleEditorView view)
			: base("ParticleEditor")
		{
			this.view = view;

			//registerEvent, etc etc
			call("initRender", view.renderPanel.Handle);
			flush();
		}

		public override void update ()
		{
			call("update");
		}
	}
}
