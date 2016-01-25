using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Editor.Source_Files.Helpers
{
	public partial class TextInputDialog : Form
	{
		private string output;
		private bool isOk;

		public TextInputDialog(String title)
		{
			InitializeComponent();

			output = "";
			isOk = false;

			this.Text = title;
		}

		private void okButton_Click(object sender, EventArgs e)
		{
			inputDone();
		}

		private void textBox_KeyUp(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
				inputDone();

			if (e.KeyCode == Keys.Escape)
				this.Close();
		}

		// Finalize input
		private void inputDone()
		{
			isOk = true;
			output = textBox.Text;
			this.Close();
		}

		public bool isInputOk()
		{
			return isOk;
		}

		public String getInputText()
		{
			return output;
		}
	}
}
