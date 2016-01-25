using Editor.Source_Files;
using Editor.Source_Files.Views;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using WeifenLuo.WinFormsUI.Docking;
using Editor.Source_Files.Objects;
using System.Diagnostics;
using Microsoft.Build.Execution;
using Microsoft.Build.Evaluation;
using Microsoft.Build.Logging;
using Microsoft.Build.Framework;
using Editor.Source_Files.CppCommunication;
using Editor.Source_Files.EntityEditor;
using Editor.Source_Files.Instances.Statistics;
using Editor.Source_Files.Instances.Stats;
using Editor.Source_Files.Helpers;
using Editor.Source_Files.Instances;
using Editor.Source_Files.Instances.ParticleEditor;
using Editor.Source_Files.Instances.SystemList;
using Editor.Source_Files.Instances.ModelImporter;
using Editor.Source_Files.Instances.ModelViewer;
using Editor.Source_Files.Instances.ProfilerAnalyzer;

namespace Editor
{
	// Component information from the engine

    public partial class MainViewBase : Form
    {
		// Stuff for the engine to work
        private Thread engineThread;

		// Own helper classes
		public ComponentInfoManager componentInfoManager = new ComponentInfoManager();

		//OperationManager handles all modifications to instances/scenes.
		public OperationManagerInstance operationManagerInstance;

		// Instance list for updating, used for stuff that just need updating in order to functino
		// TODO: consider moving other instances to this!
		List<NativeInstance> nativeInstances;

		// Lists of open editors and views
        List<EditorTab> editorList;
		List<EntityEditorInstance> entityEditorInstanceList;

		// GLOBALLY VISIBLE WINDOWS THAT ARE ALWAYS OPEN AND UNIQUE
        public LogView logView;
        public ArchiveBrowser archiveBrowser;
		public EntityListView entityList;
		public UndoListView undoListView;

        public MainViewBase(Splash splash)
        {
            InitializeComponent();

			cleanupOldRuntimeCompiledDlls();

			nativeInstances = new List<NativeInstance>();

			// First setup UI
			logView = new LogView();
			logView.Show(dockPanel, DockState.DockBottom);

			archiveBrowser = new ArchiveBrowser(this);
			archiveBrowser.Show(dockPanel, DockState.DockRight);

			entityList = new EntityListView(this);
			entityList.Show(dockPanel, DockState.DockLeft);

			undoListView = new UndoListView();
			undoListView.Show(dockPanel, DockState.DockLeftAutoHide);

			//Setup instances
			operationManagerInstance = new OperationManagerInstance(undoListView);

            editorList = new List<EditorTab>();
			entityEditorInstanceList = new List<EntityEditorInstance>();

            //createNewEditor();

            engineThread = new Thread(delegate()
			{
				for(;;)
				{
					//Loop trough instances
					int size = editorList.Count;
                    for (int i = 0; i < size; ++i )
                    {
						operationManagerInstance.flush();

                        if (editorList[i].initDone == false)
                            editorList[i].initInstance();

                        editorList[i].instance.update();
                        editorList[i].instance.flush();
                    }

					//Loop trough instances
					//TODO: Move all instances to single loop!
					for (int i = 0; i < nativeInstances.Count; ++i)
					{
						nativeInstances[i].update();
						nativeInstances[i].flush();

						if(nativeInstances[i].getShutdownState())
						{
							nativeInstances.RemoveAt(i);
							--i;
						}
					}

					//Loop trough EntityEditors
					for (int i = 0; i < entityEditorInstanceList.Count; ++i)
					{
						entityEditorInstanceList[i].update();
					}
				}
			});

            toolStripStatus.Text = "Editor started.";

            engineThread.Start();

			/*
            EntityListView elv = new EntityListView();
            elv.Show(dockPanel, DockState.DockLeft);
			*/

			/*
			EntityEditorView eev = new EntityEditorView();
            eev.Show(dockPanel, DockState.DockRight);
			*/
			//--
            this.FormClosed += OnFormClose;

			createNewEditor();

			// Little background thread to allow the splash screen to go away smoothly
			Thread splashKillerThread = new Thread(delegate()
			{
				Thread.Sleep(200);
				splash.Invoke((MethodInvoker)(() => splash.Close()));
			});

			splashKillerThread.Start();
        }

		public EditorTab getCurrentEditor()
		{
			Console.WriteLine("Only one editor supported by the tools!");
			return editorList[0];
		}

        private void createNewEditor()
        {
            EditorInstance nativeEditor = new EditorInstance(this);

            EditorView instanceView = new EditorView(nativeEditor, this);
            instanceView.Show(dockPanel, DockState.Document);
			instanceView.PanelPane.AllowDockDragAndDrop = false;

            IntPtr handle;
            unsafe
            {
                handle = (IntPtr)instanceView.instanceViewPanel.Handle.ToPointer();
            }

            EditorTab tab = new EditorTab(instanceView, nativeEditor, handle);

            editorList.Add(tab); //add to list to manage the tabs

            toolStripStatus.Text = editorList.Count + " instances running.";
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutPropellerEngine aboutWindow = new AboutPropellerEngine();

            aboutWindow.Show();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        public void OnFormClose(object sender, System.Windows.Forms.FormClosedEventArgs e)
        {
            engineThread.Abort();
        } 

        private void saveSceneToolStripMenuItem_Click(object sender, EventArgs e)
        {
			SaveSceneDialog();
        }

		public void SaveSceneDialog()
		{
			SaveFileDialog sfd = new SaveFileDialog();

			sfd.DefaultExt = "PropellerScene";
			sfd.InitialDirectory = System.Environment.CurrentDirectory;
			sfd.Filter = "Scene Files (*.PropellerScene)|*.PropellerScene|All files (*.*)|*.*";
			sfd.FilterIndex = 0;

			if (sfd.ShowDialog() == DialogResult.OK)
			{
				editorList[0].instance.saveScene(Path.GetFullPath(sfd.FileName).ToString());
				//TODO: FIND ACTIVE EDITOR
			}
		}

        private void loadSceneToolStripMenuItem_Click(object sender, EventArgs e)
        {
			OpenSceneDialog();
        }

		public void OpenSceneDialog()
		{
			OpenFileDialog ofd = new OpenFileDialog();

			ofd.DefaultExt = "PropellerScene";
			ofd.InitialDirectory = System.Environment.CurrentDirectory;
			ofd.Filter = "Scene Files (*.PropellerScene)|*.PropellerScene|All files (*.*)|*.*";
			ofd.FilterIndex = 0;

			if (ofd.ShowDialog() == DialogResult.OK)
			{
				editorList[0].instance.loadScene(Path.GetFullPath(ofd.FileName).ToString());
				operationManagerInstance.clearOperations(); //Clear undo history
				undoListView.clearUndoHistory();//Clear the GUI list of undo history
				//TODO: FIND ACTIVE EDITOR
			}
		}

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            createNewEditor();
        }

        private void compileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            runtimeCompile();
        }

		private void runtimeCompile()
        {
			/*
            string projectFileName = @"..\windows\PropellerEngine.sln";

			ConsoleLogger logger = new ConsoleLogger(LoggerVerbosity.Detailed, new WriteHandler(handleBuildOutput),null,null);

            ProjectCollection pc = new ProjectCollection();

            pc.RegisterLogger(logger);

            Dictionary<string, string> GlobalProperty = new Dictionary<string, string>();
            GlobalProperty.Add("Configuration", "EditorDebug");
            GlobalProperty.Add("Platform", "x86");

            BuildRequestData buildRequest = new BuildRequestData(projectFileName, GlobalProperty, null, new string[] { "Build" }, null);

            BuildResult buildResult = BuildManager.DefaultBuildManager.Build(new BuildParameters(pc), buildRequest);
			*/
			System.Diagnostics.Process process = new System.Diagnostics.Process();
			System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();

			//startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;

			//startInfo.Arguments = "/C call \"C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\" & devenv /edit " + path + " & exit";
            startInfo.FileName = "cmd.exe";
			startInfo.Arguments = "/C call \"C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\" & cd ../windows & msbuild /property:Configuration=\"EditorDebug\" /target:Engine";
			//startInfo.Arguments = "/C call \"C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\" & cd ../windows & msbuild /property:Configuration=\"EditorDebug\" & pause";
            startInfo.CreateNoWindow = false;

			process.StartInfo = startInfo;
			//process.OutputDataReceived += new DataReceivedEventHandler(handleBuildOutput);

            process.Start();
            process.WaitForExit();

            startInfo.FileName = "cmd.exe";
			startInfo.Arguments = "/C call \"C:\\Program Files (x86)\\Microsoft Visual Studio 12.0\\VC\\vcvarsall.bat\" & cd ../windows & msbuild /property:Configuration=\"EditorDebug\" /property:TargetName=\"GameRuntime\" /target:Game";
            startInfo.CreateNoWindow = false;

			process.StartInfo = startInfo;
			//process.OutputDataReceived += new DataReceivedEventHandler(handleBuildOutput);

            process.Start();
            process.WaitForExit();


			for(int i = 0; i < editorList.Count; ++i)
            {
                editorList[i].instance.reloadDLL();
            }
        }

		public void createTypeEditorByFilename(String file)
		{
			EntityEditorView tev = new EntityEditorView(this,getCurrentEditor().instance.getInstancePtr() , 0, file, EntityEditTargetType.TARGET_TYPE);

			for (int i = 0; i < componentInfoManager.count(); ++i)
				tev.addComponentClassNameToList(componentInfoManager.getComponentInfoByIndex(i));

			dockPanel.Invoke((MethodInvoker)(() => tev.Show(dockPanel, DockState.Float)));

			entityEditorInstanceList.Add(new EntityEditorInstance(getCurrentEditor().instance.getInstancePtr() , tev, file));
		}

		public void createEntityEditor(uint id, String name)
		{
			EntityEditorView tev = new EntityEditorView(this, getCurrentEditor().instance.getInstancePtr(), id, name, EntityEditTargetType.TARGET_ENTITY);

			for (int i = 0; i < componentInfoManager.count(); ++i)
				tev.addComponentClassNameToList(componentInfoManager.getComponentInfoByIndex(i));

			dockPanel.Invoke((MethodInvoker)(() => tev.Show(dockPanel, DockState.Float)));

			entityEditorInstanceList.Add(new EntityEditorInstance(getCurrentEditor().instance.getInstancePtr(), tev));
		}

		public void addComponentClassName(String name, String sourcePath)
		{
			componentInfoManager.addComponentInfo(new ComponentInfo(name, sourcePath));

			Console.WriteLine(name + ":" + sourcePath);
		}

		//Closes the typeeditor window "removeTypeEditor" is called by the view "close" method.
		public void closeTypeEditor(uint targetid, EntityEditTargetType targetType)
		{
			for (int i = 0; i < entityEditorInstanceList.Count; ++i)
			{
				if(entityEditorInstanceList[i].view.getId() == targetid && entityEditorInstanceList[i].view.getTargetType() == targetType)
				{
					entityEditorInstanceList[i].view.Invoke((MethodInvoker)(() => entityEditorInstanceList[i].view.Close()));

					return;
				}
			}

			//These can happen on delete that is not related to typeeditor, cannot check for errors here.
		}

		//Only removes the typeEditor, used when the window has been closed.
		public void removeTypeEditor(uint targetid, EntityEditTargetType targetType)
		{
			for (int i = 0; i < entityEditorInstanceList.Count; ++i)
			{
				if(entityEditorInstanceList[i].view.getId() == targetid && entityEditorInstanceList[i].view.getTargetType() == targetType)
				{
					entityEditorInstanceList.RemoveAt(i);

					return;
				}
			}

			//These can happen on delete that is not related to typeeditor, cannot check for errors here.
		}

		private void undoToolStripMenuItem_Click(object sender, EventArgs e)
		{
			operationManagerInstance.revert();
		}

		private void statsToolStripMenuItem_Click(object sender, EventArgs e)
		{
			// First check if there are statsviews running already...
			for(int i = 0; i < nativeInstances.Count; ++i)
			{
				if (nativeInstances[i].GetType() == typeof(StatsInstance))
				{
					logView.addMessage("[INFO] StatsView already running!");
					return;
				}
			}

			StatsView statsView = new StatsView();

			statsView.Show(dockPanel, DockState.DockBottom);

			nativeInstances.Add(new StatsInstance(getCurrentEditor().instance.getInstancePtr(), statsView));
		}

		private void saveEntityTypesToolStripMenuItem_Click(object sender, EventArgs e)
		{
			getCurrentEditor().instance.syncEntityTypesToDisk();
		}

		private void sendCommandToolStripMenuItem_Click(object sender, EventArgs e)
		{
			TextInputDialog dialog = new TextInputDialog("Command to send");

			dialog.ShowDialog(this);
			if (!dialog.isInputOk())
				return;


			String command = dialog.getInputText();

			getCurrentEditor().instance.callCCommand(command);

		}

		private void builddataDirectoryToolStripMenuItem_Click(object sender, EventArgs e)
		{
			ArchiveCreatorInstance builder = new ArchiveCreatorInstance();

			builder.addFolder("../data/");
			builder.flush();
			builder.flush();
			builder.build("game.pp");

			builder.flush();
			builder.flush();

			builder.clear();
			builder.flush();

			builder.addFolder("../enginedata/");
			builder.flush();
			builder.flush();
			builder.build("engine.pp");

			builder.flush();
			builder.flush();
			builder.flush();
		}

		private void toolStripMenuItem1_Click(object sender, EventArgs e)
		{
			ParticleEditorView pev = new ParticleEditorView();
			pev.Show();
			ParticleEditorInstance pei = new ParticleEditorInstance(pev);

			nativeInstances.Add(pei);
		}

		private void systemListToolStripMenuItem_Click(object sender, EventArgs e)
		{
			for (int i = 0; i < nativeInstances.Count; ++i)
			{
				if (nativeInstances[i].GetType() == typeof(SystemListInstance))
				{
					logView.addMessage("[INFO] SystemList already running!");
					return;
				}
			}

			SystemListView systemListView = new SystemListView();

			systemListView.Show(dockPanel, DockState.DockBottom);

			nativeInstances.Add(new SystemListInstance(getCurrentEditor().instance.getInstancePtr(), systemListView));
		}

		private void import3dModelToolStripMenuItem_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();

            ofd.InitialDirectory = System.Environment.CurrentDirectory;
            ofd.Filter = "Waveform object (*.obj)|*.obj|All files (*.*)|*.*";
            ofd.FilterIndex = 0;

            if (ofd.ShowDialog() == DialogResult.OK)
            {
				ModelImporterInstance importer = new ModelImporterInstance(this);

				importer.import(Path.GetFullPath(ofd.FileName).ToString());
            }
		}

		private void cleanupOldRuntimeCompiledDlls()
		{
			System.Diagnostics.Process process = new System.Diagnostics.Process();
			System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();

            startInfo.FileName = "cmd.exe";
			startInfo.Arguments = "/C call \"../windows/dlldel.bat\"";
            startInfo.CreateNoWindow = true;

			process.StartInfo = startInfo;
			//process.OutputDataReceived += new DataReceivedEventHandler(handleBuildOutput);

            process.Start();
			process.WaitForExit();
		}

		private void newEntityToolStripMenuItem_Click(object sender, EventArgs e)
		{
			operationManagerInstance.addEmptyEntity(getCurrentEditor().instance.getInstancePtr());
		}

		internal void createModelViewer(string file)
		{
			ModelViewerView mvw = new ModelViewerView();
			mvw.Show();
			ModelViewerInstance mvi = new ModelViewerInstance(mvw, file);

			nativeInstances.Add(mvi);
		}

		private void importTiledMapToolStripMenuItem_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();

			ofd.InitialDirectory = System.Environment.CurrentDirectory;
			ofd.Filter = "Tiled Json file (*.json)|*.json|All files (*.*)|*.*";
			ofd.FilterIndex = 0;

			if (ofd.ShowDialog() == DialogResult.OK)
			{
				getCurrentEditor().instance.importTiledMap(Path.GetFullPath(ofd.FileName).ToString());
			}
		}

		public void launchGameView(IntPtr stream)
		{
			GameInstance game = new GameInstance();

			game.startup(stream);

			nativeInstances.Add(game);
		}

		private void openPropellerProfilerDumpToolStripMenuItem_Click(object sender, EventArgs e)
		{
			OpenFileDialog ofd = new OpenFileDialog();

			ofd.InitialDirectory = System.Environment.CurrentDirectory;
			ofd.Filter = "ProfiledPropeller dump file (*.ProfiledPropeller)|*.ProfiledPropeller|All files (*.*)|*.*";
			ofd.FilterIndex = 0;

			if (ofd.ShowDialog() == DialogResult.OK)
			{
				ProfilerAnalyzerWindow analyzer = new ProfilerAnalyzerWindow(Path.GetFullPath(ofd.FileName).ToString());
				analyzer.Show();
			}
		}
	}
}
