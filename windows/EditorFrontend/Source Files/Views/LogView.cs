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
    public partial class LogView : DockContent 
    {
        public LogView()
        {
            InitializeComponent();

            logTextBox.Text = "Logger ready";
        }

		public void addMessage(String message)
        {
			logTextBox.Invoke((MethodInvoker)(() => logTextBox.Text = logTextBox.Text + "\n" + message));

            scrollToEnd();
		}

		public void logInfo(String message)
        {
            addMessage("[INFO]" + message);
        }

        public void logWarning(String message)
        {
            addMessage("[WARNING]" + message);
        }

        public void logError(String message)
        {
            addMessage("[ERROR]" + message);
        }

        private void scrollToEnd()
        {
            logTextBox.Invoke((MethodInvoker)(() => logTextBox.SelectionStart = logTextBox.Text.Length));
            logTextBox.Invoke((MethodInvoker)(() => logTextBox.ScrollToCaret()));
        }

		private void LogView_FormClosing(object sender, FormClosingEventArgs e)
		{
			e.Cancel = true; //this form cannot be closed.
		}

    }
}
