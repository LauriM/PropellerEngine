using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.Instances.ProfilerAnalyzer
{
	public class ProfilerNode
	{
		public string name { get; set; }
		public int callCount { get; set; }
		public long totalTime { get; set; } // microseconds

		public List<ProfilerNode> childs { get; set; }
	}
}
