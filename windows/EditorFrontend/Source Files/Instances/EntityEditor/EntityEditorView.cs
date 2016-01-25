using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;

namespace Editor.Source_Files.Views
{
	public enum EntityEditTargetType /* In sync with c++ */
	{
		TARGET_ENTITY = 0,
		TARGET_TYPE,
	}

	public partial class EntityEditorView : DockContent
	{
		public uint targetId { get; set; }
		public EntityEditTargetType targetType { get; set; }

		private MainViewBase rootView;

		private String name;

		// Only used for entities
		private String typeName; // "" if not set
		private bool hasType;

		IntPtr instance;

		public EntityEditorView(MainViewBase root,IntPtr inst, uint i, String name, EntityEditTargetType type)
		{
			InitializeComponent();

			hasType = false;

			instance = inst;

			rootView = root;

			targetId = i;
			targetType = type;

			Text = "Entity Editor - " + name + "[" + targetId + "]";

			this.name = name;
			nameBox.Text = name;

			//Fix right click on the treeview
			componentTreeView.MouseDown += (sender, args) => componentTreeView.SelectedNode = componentTreeView.GetNodeAt(args.X, args.Y);
		}

		private void TypeEditorView_FormClosed(object sender, FormClosedEventArgs e)
		{
			rootView.removeTypeEditor(targetId, targetType);
		}

		//add component to the GUI
		public void addComponent(uint handleid, String component)
		{
			componentTreeView.Invoke((MethodInvoker)(()=> componentTreeView.Nodes.Add("" + handleid,component)));
		}

		public void removeComponent(uint handleid)
		{
			String nodeName = "" + handleid;

			for(int i = 0; i < componentTreeView.Nodes.Count; ++i)
			{
				if(componentTreeView.Nodes[i].Name == nodeName)
				{
					componentTreeView.Invoke((MethodInvoker)(() => componentTreeView.Nodes.RemoveAt(i)));
					return;
				}
			}
		}

		//add property to the GUI
		/*
		public void addPropertyForComponent(String component, String property, String value)
		{
			for(int i = 0; i < componentTreeView.Nodes.Count; ++i)
			{
				if(componentTreeView.Nodes[i].Text == component)
				{
					//Found the correct component! Give it the property

					componentTreeView.Invoke((MethodInvoker)(() => componentTreeView.Nodes[i].Nodes.Add(property)));
					componentTreeView.Invoke((MethodInvoker)(() => componentTreeView.Nodes[i].Nodes[0].Nodes.Add(value)));
					return;
				}
			}
		}
		*/

		/*
		public void updatePropertyValueForComponent(String component, String property, String value)
		{
			for (int i = 0; i < componentTreeView.Nodes.Count; ++i)
			{
				if(componentTreeView.Nodes[i].Text == component)
				{
					//Found the correct component! 

					var propertyNodes = componentTreeView.Nodes[i].Nodes;

					//Lets find the property to be updated...
					for (int x = 0; x < propertyNodes.Count; ++x )
					{
						if(propertyNodes[x].Text == property)
						{
							componentTreeView.Invoke((MethodInvoker)(() => componentTreeView.Nodes[i].Nodes[x].Nodes[0].Text = property));
							return;
						}
					}

				}
			}

			Console.WriteLine("Could not update value of a property for component in the EntityEditor GUI");
		}
		*/

		public void addComponentClassNameToList(ComponentInfo component)
		{
			componentAddComboBox.Items.Add(component.componentName);
		}

		public uint getId() { return targetId; }
		public EntityEditTargetType getTargetType() { return targetType; }

		private void addComponentButton_Click(object sender, EventArgs e)
		{
			String componentName;

			try
			{
				componentName = componentAddComboBox.SelectedItem.ToString();
			}
			catch(NullReferenceException exp)
			{
				rootView.logView.logWarning("No component selected!");
				return;
			}

			switch(getTargetType())
			{ 
				case EntityEditTargetType.TARGET_ENTITY:
					rootView.operationManagerInstance.addComponent(instance, targetId, componentName);
					break;
				case EntityEditTargetType.TARGET_TYPE:
					rootView.operationManagerInstance.addComponentOnType(instance, name ,componentName);
					break;
			}
		}

		private void componentTreeView_KeyDown(object sender, KeyEventArgs e)
		{
			if(e.KeyData == Keys.Delete)
			{
				if (componentTreeView.SelectedNode == null)
					return;

				String componentName;

				try
				{
					componentName = componentTreeView.SelectedNode.Text;
				}
				catch(NullReferenceException exp)
				{
					rootView.logView.logWarning("No component selected!");
					return;
				}

				switch(getTargetType())
				{ 
					case EntityEditTargetType.TARGET_ENTITY:
						uint componentId = uint.Parse(componentTreeView.SelectedNode.Name);

						rootView.operationManagerInstance.removeComponent(instance, targetId, componentId);
						break;
					case EntityEditTargetType.TARGET_TYPE:
						rootView.operationManagerInstance.removeComponentOnType(instance, name, componentName);
						break;
				}
			}
		}

		// Removes all components from the UI. Used on clean&refresh.
		internal void removeAllComponents()
		{
			componentTreeView.Invoke((MethodInvoker)(() => componentTreeView.Nodes.Clear()));
		}

		internal void setEntityType(string entityType)
		{
			// This entity is managed by a type!
			typeName = entityType;

			//Show the fields in the editor
			typeLabel.Visible = true;
			typeTextBox.Visible = true;

			if (typeName == "")
			{
				typeTextBox.Text = "!No type!";
			}
			else
			{
				typeTextBox.Text = typeName;
			}
		}

		private void componentTreeView_MouseUp_1(object sender, MouseEventArgs e)
		{
			if (e.Button != MouseButtons.Right)
				return;

			componentContextMenu.Show(componentTreeView, e.Location);
		}

		private void editComponentSourceButton_Click(object sender, EventArgs e)
		{
			TreeNode node = componentTreeView.SelectedNode;

			if (node == null)
				return; // invalid selection

			String componentName = node.Text;

			ComponentInfo info = rootView.componentInfoManager.getComponentInfoByName(componentName);

			if (info == null)
			{
				rootView.logView.addMessage("Invalid componentname");
				return;
			}

			System.Diagnostics.Process.Start(@info.componentPath);
		}

		private void nameBox_Leave(object sender, EventArgs e)
		{
			tryUpdateName();
		}

		private void tryUpdateName()
		{
			if(nameBox.Text != name)
			{
				if(targetType == EntityEditTargetType.TARGET_TYPE)
				{
					rootView.logView.logWarning("Renaming types not implemented.");
					return;
				}

				//Update
				rootView.operationManagerInstance.renameEntity(instance, targetId, nameBox.Text);

				name = nameBox.Text;
			}
		}

		private void nameBox_KeyUp(object sender, KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Enter)
				tryUpdateName();
		}
	}
}
