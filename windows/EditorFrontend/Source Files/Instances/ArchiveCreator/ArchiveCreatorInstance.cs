using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.Instances
{
	public class ArchiveCreatorInstance : NativeInstance
	{
		public ArchiveCreatorInstance()
			: base("ArchiveCreator")
		{
		}

		public void addFolder(String folder)
		{
			call("addFolder", folder);
			flush();
		}

		public void addFile(String file)
		{
			call("addFile", file);
			flush();
		}

		public void build(String file)
		{
			call("build", file);
			flush();
		}

		internal void clear()
		{
			call("clear");
			flush();
		}
	}
}
