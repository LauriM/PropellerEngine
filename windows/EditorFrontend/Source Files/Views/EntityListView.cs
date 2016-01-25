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
    public partial class EntityListView : DockContent
    {
		private MainViewBase rootView; //Required for delete calls to engine

        public EntityListView(MainViewBase r)
        {
            InitializeComponent();

			rootView = r;
        }

		//Adds the entity to the list
		public void addEntity(uint id, String name)
		{
			Console.WriteLine(id);
			//Need identification!
			treeView.Invoke((MethodInvoker)(() => treeView.Nodes.Add("" + id, name)));
		}

		public void removeEntity(uint id)
		{
			String key = "" + id;

			if(!treeView.Nodes.ContainsKey(key))
				return;

			treeView.Invoke((MethodInvoker)(() => treeView.Nodes.RemoveByKey(key)));
			
			//Lets close the typeEditors that could have been open for that type.
			rootView.closeTypeEditor(id, EntityEditTargetType.TARGET_ENTITY);
		}

		public void entityListViewRenameEntity(uint entityId, String name)
		{
			Console.WriteLine("update " + entityId + " " + name);

			String key = "" + entityId;

			if (!treeView.Nodes.ContainsKey(key))
				return;

			treeView.Invoke((MethodInvoker)(() => treeView.Nodes[treeView.Nodes.IndexOfKey(key)].Text = name));
		}

		public void entityListClear()
		{
			treeView.Invoke((MethodInvoker)(() => treeView.Nodes.Clear()));
		}

		private void treeView_KeyDown(object sender, KeyEventArgs e)
		{
			if (e.KeyData == Keys.Delete)
			{
				if (treeView.SelectedNode == null)
					return; //nothing selected

				uint id = uint.Parse(treeView.SelectedNode.Name);

				rootView.operationManagerInstance.removeEntityById(rootView.getCurrentEditor().instance.getInstancePtr(), id); 
				rootView.closeTypeEditor(id, EntityEditTargetType.TARGET_ENTITY);
			}
		}

		private void treeView_DoubleClick(object sender, EventArgs e)
		{
			if (treeView.SelectedNode == null)
				return;

			String name = treeView.SelectedNode.Name;

			uint id = uint.Parse(name);

			rootView.createEntityEditor(id, name);
		}

		private void EntityListView_FormClosing(object sender, FormClosingEventArgs e)
		{
			e.Cancel = true;
		}

    }
}
