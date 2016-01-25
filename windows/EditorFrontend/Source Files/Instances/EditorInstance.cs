using Editor.Source_Files.Helpers;
using Editor.Source_Files.Views;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Source_Files
{
    public class EditorInstance : NativeInstance
    {
        public void addMessage(String message)
        {
            Console.WriteLine(message);
        }

		MainViewBase mainView;

		public EditorInstance(MainViewBase m)  //MainView is requested to get the event bindings to the editor windows done.
            : base("GameEditor")
        {
			mainView = m;

            registerEvent("addMessage", mainView.logView , typeof(LogView).GetMethod("addMessage"));
            registerEvent("logInfo", mainView.logView, typeof(LogView).GetMethod("logInfo"));
            registerEvent("logWarning", mainView.logView, typeof(LogView).GetMethod("logWarning"));
            registerEvent("logError", mainView.logView, typeof(LogView).GetMethod("logError"));

			registerEvent("addNode", mainView.archiveBrowser, typeof(ArchiveBrowser).GetMethod("addNode"));
			registerEvent("clearNodes", mainView.archiveBrowser, typeof(ArchiveBrowser).GetMethod("clearNodes"));

			registerEvent("addComponentClassName", mainView, typeof(MainViewBase).GetMethod("addComponentClassName"));

			registerEvent("entityListAddNode", mainView.entityList, typeof(EntityListView).GetMethod("addEntity"));
			registerEvent("entityListRemoveNode", mainView.entityList, typeof(EntityListView).GetMethod("removeEntity"));
			registerEvent("entityListClear", mainView.entityList, typeof(EntityListView).GetMethod("entityListClear"));
			registerEvent("entityListRenameEntity", mainView.entityList, typeof(EntityListView).GetMethod("entityListViewRenameEntity"));

			//Same editor, different targetType
			registerEvent("createTypeEditor", mainView, typeof(MainViewBase).GetMethod("createTypeEditor"));
			registerEvent("createEntityEditor", mainView, typeof(MainViewBase).GetMethod("createEntityEditor"));

			registerEvent("launchGameView", mainView, typeof(MainViewBase).GetMethod("launchGameView"));
        }

		internal void requestGameViewLaunch()
		{
			call("requestGameViewLaunch");
		}

		public override void update ()
        {
            call("update");
		}

		public void initializeRenderer(IntPtr handle)
        {
            unsafe
            {
                call("initializeRenderer", handle);
            }
            flush();
        }

		public void initialize()
        {
            call("initialize");
            flush();
        }

        public void saveScene(String path)
        {
            call("saveScene", path);
        }

		public void loadScene(String path)
        {
            call("loadScene", path);
        }

		public void removeEntity(int handle)
		{
			call("removeEntity", handle);
		}

		public void addDummy(int x, int y)
        {
			call("addDummy",x, y);
        }

		public void keyDown(int code)
        {
            call("keyDown", code);
        }

		public void keyUp(int code)
        {
            call("keyUp", code);
        }

		public void reloadDLL()
        {
            call("reloadDLL");
        }

		public void requestTypeEditor(string file)
		{
			call("requestTypeEditor", file);
		}

		public void syncEntityTypesToDisk()
		{
			call("syncEntityTypesToDisk");
		}

		public void createNewEntityType(String name)
		{
			call("createNewEntityType", name);
		}

		// Call Console command
		internal void callCCommand(string command)
		{
			call("callCCommand", command);
		}

		internal void mouseDeltaInput(int p1, int p2)
		{
			call("mouseDeltaInput", (float)p1, (float)p2);
		}

		internal void reloadArchiveBrowserList()
		{
			call("reloadArchiveBrowserList");
		}

		internal void importTiledMap(String filename)
		{
			call("importTiledMap", filename);
		}

		internal void toggle2D3D()
		{
			call("toggle2D3D");
		}

		internal void stopEngine()
		{
			mainView.operationManagerInstance.clearOperations();
			call("stopEngine");
		}

		internal void pauseEngine()
		{
			call("pauseEngine");
		}

		internal void runEngine()
		{
			mainView.operationManagerInstance.clearOperations();
			call("runEngine");
		}
	}
}
