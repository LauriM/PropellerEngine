using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Data;
using Newtonsoft.Json;

namespace Editor.Source_Files.Instances.ProfilerAnalyzer
{
	public partial class ProfilerAnalyzerWindow : Form
	{
		TreeNode currentNode;

		public ProfilerAnalyzerWindow(String pathToProfiledPropeller)
		{
			InitializeComponent();

			String jsonString = File.ReadAllText(pathToProfiledPropeller);

			ProfilerDump dump = JsonConvert.DeserializeObject<ProfilerDump>(jsonString);

			ProfilerNode node = dump.root;

			currentNode = treeView.Nodes.Add("# " + node.name);

			addChildsToTree(dump.root, null);
		}

		private void addChildsToTree(ProfilerNode node, ProfilerNode parent)
		{
			// Add current info
			float averageTime = 0;

			if (node.totalTime != 0)
				averageTime = node.totalTime / node.callCount;

			decimal percentageOfParent = 0;

			if (parent != null && parent.totalTime != 0)
				percentageOfParent = Math.Round(new Decimal(node.totalTime) / new Decimal(parent.totalTime), 3) * 100;

			currentNode = currentNode.Nodes.Add(percentageOfParent + "% | " + node.name + " avrg: " + Math.Round(averageTime / 1000, 4) + "ms");

			if(percentageOfParent > 30)
				currentNode.BackColor = Color.Yellow;

			if (percentageOfParent > 60)
				currentNode.BackColor = Color.Orange;

			if (percentageOfParent > 80)
				currentNode.BackColor = Color.Red;

			if (node.childs != null)
			{
				// Add childs
				for (int i = 0; i < node.childs.Count; ++i)
				{
					addChildsToTree(node.childs[i], node);
				}
			}

			currentNode = currentNode.Parent;
		}

	}
}
