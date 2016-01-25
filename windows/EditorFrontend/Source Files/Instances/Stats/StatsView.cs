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

namespace Editor.Source_Files.Instances.Stats
{
	public partial class StatsView : DockContent
	{
		public bool isClosed { get; set; }

		public StatsView()
		{
			InitializeComponent();
			isClosed = false;

			chart.Series.Clear();
		}

		public void addPoint(String serie, double value)
		{
			if (isClosed)
				return;

			// Check if dataselectionbox item exists.
			if(!dataSelectionBox.Items.Contains(serie))
			{
				dataSelectionBox.Invoke((MethodInvoker)(() => dataSelectionBox.Items.Add(serie))); //create if not
			}

			if (chart.Series.FindByName(serie) == null)
				return;

			chart.Invoke((MethodInvoker)(() => chart.Series[serie].Points.Add(value)));
		}

		private void StatsView_FormClosed(object sender, FormClosedEventArgs e)
		{
			isClosed = true;
		}

		private void dataSelectionBox_ItemCheck(object sender, ItemCheckEventArgs e)
		{
			String serie = dataSelectionBox.GetItemText(dataSelectionBox.Items[e.Index]);

			if (e.NewValue == CheckState.Checked)
			{
				if (chart.Series.FindByName(serie) == null)
				{
					chart.Invoke((MethodInvoker)(() => chart.Series.Add(serie)));
				}
			}

			if(e.NewValue == CheckState.Unchecked)
			{
				chart.Series.Remove(chart.Series[serie]);
			}
		}

		private void clearButton_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < chart.Series.Count; ++i)
				chart.Series[i].Points.Clear();
		}

		private void resetButton_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < dataSelectionBox.Items.Count; ++i)
				dataSelectionBox.SetItemCheckState(i,CheckState.Unchecked);
		}

	}
}
