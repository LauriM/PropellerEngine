using Editor.Source_Files.Helpers;
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
    public partial class ArchiveBrowser : DockContent
    {
		enum ImageType
		{
			PROPELLER = 0,
			TYPE,
			IMAGE,
		};

		private MainViewBase rootView;
		private Boolean mouseDown; // for drag & drop

        public ArchiveBrowser(MainViewBase root)
        {
            InitializeComponent();

			rootView = root;

			/*
			System.Drawing.Icon icon = System.Drawing.Icon.ExtractAssociatedIcon("../data/dummy.type");
			archiveImageList.Images.Add(icon);
			*/

			treeView.Nodes.Add("0", "/data/", 0);
        }

		public void addNode(String node)
		{
			ImageType type = extractTypeFromFilename(node);
			treeView.Invoke((MethodInvoker)(() => treeView.Nodes[0].Nodes.Add(node, node, (int)type)));

			treeView.Invoke((MethodInvoker)(() => treeView.ExpandAll()));
			updateFileCountLabel();
		}

		public void clearNodes()
		{
			treeView.Invoke((MethodInvoker)(() => treeView.Nodes[0].Nodes.Clear()));
			updateFileCountLabel();
		}

		private void updateFileCountLabel()
		{
			String str = "Total of " + treeView.GetNodeCount(true) + " files.";

			fileCountLabel.Invoke((MethodInvoker)(() => fileCountLabel.Text = str));
		}

		private ImageType extractTypeFromFilename(String str)
		{
			ImageType output = ImageType.PROPELLER;

			if (str.Substring(str.LastIndexOf(".") + 1) == "png")
				output = ImageType.IMAGE;

			if (str.Substring(str.LastIndexOf(".") + 1) == "type")
				output = ImageType.TYPE;

			return output;
		}

		private void treeView_DoubleClick(object sender, EventArgs e)
		{
			//We have open event coming up!

			if (treeView.SelectedNode == null)
				return;

			//Lets check the file type...
			String file = treeView.SelectedNode.Name;
			switch(file.Substring(file.LastIndexOf(".") + 1 ).ToLower())
			{
				case "type":
					//Create a call to c++ to init the window.
					//After that c++ should make follow up calls to fill up the data into it.
					rootView.createTypeEditorByFilename(file);
					break;
				case "propellermodel":
					//Open the model in the model viewer instance
					rootView.createModelViewer(file);
					break;
			}

		}

		private void toolStripMenuItemCreateEntity_Click(object sender, EventArgs e)
		{
			TextInputDialog dialog = new TextInputDialog("Name for the type");

			dialog.ShowDialog(this);
			if (!dialog.isInputOk())
				return;

			String name = dialog.getInputText() + ".type";

			rootView.getCurrentEditor().instance.createNewEntityType(name);
		}


		private void ArchiveBrowser_FormClosing(object sender, FormClosingEventArgs e)
		{
			e.Cancel = true;
		}

		private void treeView_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button != MouseButtons.Right)
				return;

			contextMenu.Show(treeView, e.Location);
		}

		private void treeView_MouseLeave(object sender, EventArgs e)
		{
			if (treeView.SelectedNode == null)
				return;

			String assetName = treeView.SelectedNode.Text;

			DragDropEffects eff = DoDragDrop(assetName, DragDropEffects.All);

			if (eff == DragDropEffects.All)
			{
				Console.WriteLine("Eff ok!");
			}
		}

		private void refreshButton_Click(object sender, EventArgs e)
		{
			updateFileCountLabel();
			rootView.getCurrentEditor().instance.reloadArchiveBrowserList();
		}

    }
}
