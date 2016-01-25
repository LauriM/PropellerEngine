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

namespace Editor.Source_Files.Views
{
	public partial class UndoListView : DockContent
	{
		public UndoListView()
		{
			InitializeComponent();
		}

		public void addEventString(String eventDesc)
		{
			undoList.Invoke((MethodInvoker)(() => undoList.Items.Add(eventDesc)));
		}

		public void revertEvent()
		{
			if(undoList.Items.Count > 0)
				undoList.Invoke((MethodInvoker)(() => undoList.Items.RemoveAt(undoList.Items.Count - 1)));
		}

		internal void clearUndoHistory()
		{
			undoList.Invoke((MethodInvoker)(() => undoList.Items.Clear()));
		}

		private void UndoListView_FormClosing(object sender, FormClosingEventArgs e)
		{
			e.Cancel = true;
		}
	}
}
