using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;

namespace Editor.Source_Files.Instances.SystemList
{
	public partial class SystemListView : DockContent
	{
		public SystemListView()
		{
			InitializeComponent();
		}

		public void addSystem(String systemName, bool running)
		{
			//TODO: find if it already exists!
			systemListBox.Items.Add(systemName, running);
		}

		private void SystemListView_FormClosed(object sender, FormClosedEventArgs e)
		{
			Console.WriteLine("SystemListView closing NOT IMPLEMENTED!");
		}

	}
}
