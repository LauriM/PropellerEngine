using Editor.Source_Files.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.EntityEditor
{
	class EntityEditorInstance : NativeInstance
	{
		public EntityEditorView view { get; set; } 

		public EntityEditorInstance(IntPtr instancePtr, EntityEditorView view)
			: base("EntityEditor")
		{
			this.view = view;

			registerEvents();

			call("setType", (UInt64)view.getTargetType());
			flush(); //TODO: FIX THIS MULTIPLE FLUSH ISSUE!
			call("setTargetId", view.getId());
			flush();
			call("setTargetInstance", instancePtr);
			flush();
		}

		public EntityEditorInstance(IntPtr instancePtr, EntityEditorView view, String filename)
			: base("EntityEditor")
		{
			this.view = view;

			registerEvents();

			call("setType", (UInt64)view.getTargetType());
			flush(); //TODO: FIX THIS MULTIPLE FLUSH ISSUE!
			call("setTargetTypeName", filename);
			flush();
			call("setTargetInstance", instancePtr);
			flush();

			// Refresh the GUI for the types data.
			call("update");
		}

		private void registerEvents()
		{
			registerEvent("addComponent", this, typeof(EntityEditorInstance).GetMethod("addComponent"));
			registerEvent("removeComponent", this, typeof(EntityEditorInstance).GetMethod("removeComponent"));
			registerEvent("removeAllComponents", this, typeof(EntityEditorInstance).GetMethod("removeAllComponents"));
			registerEvent("setName", this, typeof(EntityEditorInstance).GetMethod("setName"));
			registerEvent("setEntityType", this, typeof(EntityEditorInstance).GetMethod("setEntityType"));
		}

		~EntityEditorInstance()
		{
			flush();
		}

		public void setEntityType(String entityType)
		{
			view.setEntityType(entityType);
		}

		public void setName(String name)
		{
			view.nameBox.Text = name;
		}

		//Adds component to the editor
		public void addComponent(uint handleid, String name)
		{
			view.addComponent(handleid, name);
		}

		public void removeComponent(uint componentid)
		{
			view.removeComponent(componentid);
		}

		public void removeAllComponents()
		{
			view.removeAllComponents();
		}

		public void update()
		{
			call("update");
			flush();
		}
	}
}
