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

namespace Editor.Source_Files
{
    public partial class EditorView : DockContent
    {
        EditorInstance editor;
		MainViewBase rootView;

		private Boolean mouseLocked;

		// to count delta
		private int lastPosX;
		private int lastPosY;

		// to move mouse to center of the container
		private Point mouseStartLocation;

		// ignore the mouse centering
		private Boolean ignoreMouse;

        public EditorView(EditorInstance e, MainViewBase r)
        {
            InitializeComponent();
            editor = e;
			rootView = r;

			mouseLocked = false;
        }

        private void EditorView_KeyDown(object sender, KeyEventArgs e)
        {
			//TODO: repeated code and manual conversion! Fix this ! (C# keycode to propellerKey)
			if(e.KeyCode == Keys.W)
            {
                editor.keyDown(23);
            }

			if (e.KeyCode == Keys.S)
			{
				editor.keyDown(19);
			}

			if (e.KeyCode == Keys.A)
			{
				editor.keyDown(1);
			}

			if (e.KeyCode == Keys.D)
			{
				editor.keyDown(4);
			}
        }

        private void EditorView_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.W)
            {
                editor.keyUp(23);
            }
			if (e.KeyCode == Keys.S)
			{
				editor.keyUp(19);
			}

			if (e.KeyCode == Keys.A)
			{
				editor.keyUp(1);
			}

			if (e.KeyCode == Keys.D)
			{
				editor.keyUp(4);
			}
        }

		private void instanceViewPanel_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				mouseLocked = true;

				lastPosX = e.X;
				lastPosY = e.Y;

				mouseStartLocation = Cursor.Position;

				Cursor.Hide();
			}

			splitContainer.Focus();
		}

		private void instanceViewPanel_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				mouseLocked = false;

				Cursor.Position = mouseStartLocation;

				Cursor.Show();
			}
		}

		private void instanceViewPanel_MouseMove(object sender, MouseEventArgs e)
		{
			if (mouseLocked == true)
			{
				if (ignoreMouse)
				{
					ignoreMouse = false;

					lastPosX = e.X;
					lastPosY = e.Y;

					return; // don't handle the input when the mouse is centered to the start position
				}

				int deltaX = e.X - lastPosX;
				int deltaY = e.Y - lastPosY;

				editor.mouseDeltaInput(deltaX * 1, deltaY * 1);

				lastPosX = e.X;
				lastPosY = e.Y;

				Cursor.Position = mouseStartLocation;
				ignoreMouse = true;
			}
		}

		private void instanceViewPanel_DragDrop(object sender, DragEventArgs e)
		{
			if (e.Data.GetDataPresent(DataFormats.StringFormat))
			{
				string str = (string)e.Data.GetData(
					DataFormats.StringFormat);

				rootView.operationManagerInstance.addEntityByType(editor.getInstancePtr(), str, 0, 0);
			}
		}

		private void instanceViewPanel_DragOver(object sender, DragEventArgs e)
		{
			e.Effect = DragDropEffects.None;

			// check type of the drag
			if (e.Data.GetDataPresent(DataFormats.StringFormat))
			{

				string str = (string)e.Data.GetData(
					DataFormats.StringFormat);

				if(str.Contains(".type"))
					e.Effect = DragDropEffects.All;
			}
		}

		private void toggle2d3dbutton_Click(object sender, EventArgs e)
		{
			editor.toggle2D3D();
		}

		private void openButton_Click(object sender, EventArgs e)
		{
			rootView.OpenSceneDialog();
		}

		private void saveButton_Click(object sender, EventArgs e)
		{
			rootView.SaveSceneDialog();
		}

		private void playButton_Click(object sender, EventArgs e)
		{
			rootView.getCurrentEditor().instance.runEngine();
		}

		private void pauseButton_Click(object sender, EventArgs e)
		{
			rootView.getCurrentEditor().instance.pauseEngine();
		}

		private void stopButton_Click(object sender, EventArgs e)
		{
			rootView.getCurrentEditor().instance.stopEngine();
		}

		private void launchGame_Click(object sender, EventArgs e)
		{
			// Request the editor instance to send the scene into a stream and launch the GameView from there
			rootView.getCurrentEditor().instance.requestGameViewLaunch();
		}
    }
}
