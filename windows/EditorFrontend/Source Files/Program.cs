using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Text;
using Editor.Source_Files;

namespace Editor
{
    static class Program
    {

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {

			//Clear old dll's for the runtime.
			/*
            System.Diagnostics.Process process = new System.Diagnostics.Process();
            System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
            startInfo.FileName = "cmd.exe";
            startInfo.Arguments = "/C call \"../windows/dlldel.bat\"";
            startInfo.UseShellExecute = true;
            process.StartInfo = startInfo;
          //  process.Start();
			*/

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

			Splash splash = new Splash();
			splash.Show();

            Application.Run(new MainViewBase(splash));
        }
    }
}
