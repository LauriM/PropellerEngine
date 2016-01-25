using Editor.Source_Files.Views;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files.CppCommunication
{
	public class OperationManagerInstance : NativeInstance
	{
		private UndoListView undoListView;

		public OperationManagerInstance(UndoListView u)
			: base("OperationManager")
		{
			undoListView = u;

			//Undo list visual update stuff
			registerEvent("addUndoListEvent", undoListView, typeof(UndoListView).GetMethod("addEventString"));
			registerEvent("revertUndoListEvent", undoListView, typeof(UndoListView).GetMethod("revertEvent"));
		}

		// General actions
		public void revert()
		{
			call("revert");
		}

		// Commands
		public void addEntityByType(IntPtr instance, String type, int x, int y)
		{
			call("addEntity", instance, type, x, y);
		}

		internal void removeEntityById(IntPtr instance, uint id)
		{
			call("removeEntity", instance, id);
		}

		internal void clearOperations()
		{
			call("clear");
			undoListView.clearUndoHistory();
		}

		internal void addComponent(IntPtr instance, uint entityId, String componentName)
		{
			//Enum converted to Int32
			call("addComponent", instance, entityId, componentName);
		}

		internal void removeComponent(IntPtr instance, uint entityId, uint componentId)
		{
			//Enum converted to Int32
			call("removeComponent", instance, entityId, componentId);
		}

		internal void addComponentOnType(IntPtr instance, String typeName, String componentName)
		{
			call("addComponentOnType", instance, typeName, componentName);
		}

		internal void removeComponentOnType(IntPtr instance, String typeName, String componentName)
		{ 
			call("removeComponentOnType", instance, typeName, componentName);
		}

		internal void renameEntity(IntPtr instance, uint targetId, string name)
		{
			call("renameEntity", instance, targetId, name);
		}

		internal void addEmptyEntity(IntPtr instance)
		{
			call("addEmptyEntity", instance);
		}
	}
}
