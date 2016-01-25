using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Editor.Source_Files.Instances.ModelViewer
{
	public partial class ModelViewerView : Form
	{
		private ModelViewerInstance instance;
		private Point mouseStartLocation;
		private int lastPosX;
		private bool mouseLocked;
		private int lastPosY;
		private bool ignoreMouse;

		public ModelViewerView()
		{
			InitializeComponent();

			mouseLocked = false;
		}

		private void quitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			//TODO: killing the editor correctly not implemented
			throw new NotImplementedException();
		}

		internal void setModelViewerInstance(ModelViewerInstance modelViewerInstance)
		{
			instance = modelViewerInstance;
		}

		private void ModelViewerView_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.W)
			{
				instance.keyDown(23);
			}

			if (e.KeyCode == Keys.S)
			{
				instance.keyDown(19);
			}

			if (e.KeyCode == Keys.A)
			{
				instance.keyDown(1);
			}

			if (e.KeyCode == Keys.D)
			{
				instance.keyDown(4);
			}
		}

		private void ModelViewerView_KeyUp(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.W)
			{
				instance.keyUp(23);
			}
			if (e.KeyCode == Keys.S)
			{
				instance.keyUp(19);
			}

			if (e.KeyCode == Keys.A)
			{
				instance.keyUp(1);
			}

			if (e.KeyCode == Keys.D)
			{
				instance.keyUp(4);
			}
		}

		private void renderPanel_MouseDown(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				mouseLocked = true;

				lastPosX = e.X;
				lastPosY = e.Y;

				mouseStartLocation = Cursor.Position;

				Cursor.Hide();
			}

			this.Focus();
		}

		private void renderPanel_MouseUp(object sender, MouseEventArgs e)
		{
			if (e.Button == MouseButtons.Right)
			{
				mouseLocked = false;

				Cursor.Position = mouseStartLocation;

				Cursor.Show();
			}
		}

		private void renderPanel_MouseMove(object sender, MouseEventArgs e)
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

				instance.mouseDeltaInput(deltaX * 1, deltaY * 1);

				lastPosX = e.X;
				lastPosY = e.Y;

				Cursor.Position = mouseStartLocation;
				ignoreMouse = true;
			}
		}

		private void toggleWireframeToolStripMenuItem_Click(object sender, EventArgs e)
		{
			instance.toggleWireframe();
		}

		private void toggleGridToolStripMenuItem_Click(object sender, EventArgs e)
		{
			instance.toggleGrid();
		}
	}
}
