using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.Instances.ModelImporter
{
	class ModelImporterInstance : NativeInstance
	{
		MainViewBase root;

		public ModelImporterInstance(MainViewBase rootView)
			: base("ModelImporterInstance")
		{
			root = rootView;
			registerEvent("requestArchiveRefresh", this, typeof(ModelImporterInstance).GetMethod("requestArchiveRefresh"));
		}

		public void import(String filename)
		{
			call("import", filename);
			flush();
		}

		public void requestArchiveRefresh()
		{
			// the model conversion is done and archive browser should be refreshed.
			root.getCurrentEditor().instance.reloadArchiveBrowserList();
		}
	}
}
