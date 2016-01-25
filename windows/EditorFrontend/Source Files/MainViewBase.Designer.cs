namespace Editor
{
    partial class MainViewBase
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			WeifenLuo.WinFormsUI.Docking.DockPanelSkin dockPanelSkin1 = new WeifenLuo.WinFormsUI.Docking.DockPanelSkin();
			WeifenLuo.WinFormsUI.Docking.AutoHideStripSkin autoHideStripSkin1 = new WeifenLuo.WinFormsUI.Docking.AutoHideStripSkin();
			WeifenLuo.WinFormsUI.Docking.DockPanelGradient dockPanelGradient1 = new WeifenLuo.WinFormsUI.Docking.DockPanelGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient1 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.DockPaneStripSkin dockPaneStripSkin1 = new WeifenLuo.WinFormsUI.Docking.DockPaneStripSkin();
			WeifenLuo.WinFormsUI.Docking.DockPaneStripGradient dockPaneStripGradient1 = new WeifenLuo.WinFormsUI.Docking.DockPaneStripGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient2 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.DockPanelGradient dockPanelGradient2 = new WeifenLuo.WinFormsUI.Docking.DockPanelGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient3 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.DockPaneStripToolWindowGradient dockPaneStripToolWindowGradient1 = new WeifenLuo.WinFormsUI.Docking.DockPaneStripToolWindowGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient4 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient5 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.DockPanelGradient dockPanelGradient3 = new WeifenLuo.WinFormsUI.Docking.DockPanelGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient6 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			WeifenLuo.WinFormsUI.Docking.TabGradient tabGradient7 = new WeifenLuo.WinFormsUI.Docking.TabGradient();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainViewBase));
			this.dockPanel = new WeifenLuo.WinFormsUI.Docking.DockPanel();
			this.menuStrip = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.saveSceneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.loadSceneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.editToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.undoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.sceneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.newEntityToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.importTiledMapToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.engineToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.saveEntityTypesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.compileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.systemListToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.statsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.sendCommandToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.builddataDirectoryToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.dataToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.import3dModelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.helpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.statusStrip = new System.Windows.Forms.StatusStrip();
			this.toolStripStatus = new System.Windows.Forms.ToolStripStatusLabel();
			this.openPropellerProfilerDumpToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.menuStrip.SuspendLayout();
			this.statusStrip.SuspendLayout();
			this.SuspendLayout();
			// 
			// dockPanel
			// 
			this.dockPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.dockPanel.Location = new System.Drawing.Point(0, 24);
			this.dockPanel.Name = "dockPanel";
			this.dockPanel.Size = new System.Drawing.Size(1387, 854);
			dockPanelGradient1.EndColor = System.Drawing.SystemColors.ControlLight;
			dockPanelGradient1.StartColor = System.Drawing.SystemColors.ControlLight;
			autoHideStripSkin1.DockStripGradient = dockPanelGradient1;
			tabGradient1.EndColor = System.Drawing.SystemColors.Control;
			tabGradient1.StartColor = System.Drawing.SystemColors.Control;
			tabGradient1.TextColor = System.Drawing.SystemColors.ControlDarkDark;
			autoHideStripSkin1.TabGradient = tabGradient1;
			autoHideStripSkin1.TextFont = new System.Drawing.Font("Segoe UI", 9F);
			dockPanelSkin1.AutoHideStripSkin = autoHideStripSkin1;
			tabGradient2.EndColor = System.Drawing.SystemColors.ControlLightLight;
			tabGradient2.StartColor = System.Drawing.SystemColors.ControlLightLight;
			tabGradient2.TextColor = System.Drawing.SystemColors.ControlText;
			dockPaneStripGradient1.ActiveTabGradient = tabGradient2;
			dockPanelGradient2.EndColor = System.Drawing.SystemColors.Control;
			dockPanelGradient2.StartColor = System.Drawing.SystemColors.Control;
			dockPaneStripGradient1.DockStripGradient = dockPanelGradient2;
			tabGradient3.EndColor = System.Drawing.SystemColors.ControlLight;
			tabGradient3.StartColor = System.Drawing.SystemColors.ControlLight;
			tabGradient3.TextColor = System.Drawing.SystemColors.ControlText;
			dockPaneStripGradient1.InactiveTabGradient = tabGradient3;
			dockPaneStripSkin1.DocumentGradient = dockPaneStripGradient1;
			dockPaneStripSkin1.TextFont = new System.Drawing.Font("Segoe UI", 9F);
			tabGradient4.EndColor = System.Drawing.SystemColors.ActiveCaption;
			tabGradient4.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
			tabGradient4.StartColor = System.Drawing.SystemColors.GradientActiveCaption;
			tabGradient4.TextColor = System.Drawing.SystemColors.ActiveCaptionText;
			dockPaneStripToolWindowGradient1.ActiveCaptionGradient = tabGradient4;
			tabGradient5.EndColor = System.Drawing.SystemColors.Control;
			tabGradient5.StartColor = System.Drawing.SystemColors.Control;
			tabGradient5.TextColor = System.Drawing.SystemColors.ControlText;
			dockPaneStripToolWindowGradient1.ActiveTabGradient = tabGradient5;
			dockPanelGradient3.EndColor = System.Drawing.SystemColors.ControlLight;
			dockPanelGradient3.StartColor = System.Drawing.SystemColors.ControlLight;
			dockPaneStripToolWindowGradient1.DockStripGradient = dockPanelGradient3;
			tabGradient6.EndColor = System.Drawing.SystemColors.InactiveCaption;
			tabGradient6.LinearGradientMode = System.Drawing.Drawing2D.LinearGradientMode.Vertical;
			tabGradient6.StartColor = System.Drawing.SystemColors.GradientInactiveCaption;
			tabGradient6.TextColor = System.Drawing.SystemColors.InactiveCaptionText;
			dockPaneStripToolWindowGradient1.InactiveCaptionGradient = tabGradient6;
			tabGradient7.EndColor = System.Drawing.Color.Transparent;
			tabGradient7.StartColor = System.Drawing.Color.Transparent;
			tabGradient7.TextColor = System.Drawing.SystemColors.ControlDarkDark;
			dockPaneStripToolWindowGradient1.InactiveTabGradient = tabGradient7;
			dockPaneStripSkin1.ToolWindowGradient = dockPaneStripToolWindowGradient1;
			dockPanelSkin1.DockPaneStripSkin = dockPaneStripSkin1;
			this.dockPanel.Skin = dockPanelSkin1;
			this.dockPanel.TabIndex = 1;
			// 
			// menuStrip
			// 
			this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.editToolStripMenuItem,
            this.sceneToolStripMenuItem,
            this.engineToolStripMenuItem,
            this.dataToolStripMenuItem,
            this.helpToolStripMenuItem});
			this.menuStrip.Location = new System.Drawing.Point(0, 0);
			this.menuStrip.Name = "menuStrip";
			this.menuStrip.Size = new System.Drawing.Size(1387, 24);
			this.menuStrip.TabIndex = 3;
			this.menuStrip.Text = "menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.toolStripSeparator1,
            this.toolStripMenuItem1,
            this.toolStripSeparator2,
            this.saveSceneToolStripMenuItem,
            this.loadSceneToolStripMenuItem,
            this.exitToolStripMenuItem});
			this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
			this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
			this.fileToolStripMenuItem.Text = "File";
			// 
			// newToolStripMenuItem
			// 
			this.newToolStripMenuItem.Name = "newToolStripMenuItem";
			this.newToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
			this.newToolStripMenuItem.Text = "New";
			this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(158, 6);
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size(161, 22);
			this.toolStripMenuItem1.Text = "New effect...";
			this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(158, 6);
			// 
			// saveSceneToolStripMenuItem
			// 
			this.saveSceneToolStripMenuItem.Name = "saveSceneToolStripMenuItem";
			this.saveSceneToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
			this.saveSceneToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
			this.saveSceneToolStripMenuItem.Text = "Save as...";
			this.saveSceneToolStripMenuItem.Click += new System.EventHandler(this.saveSceneToolStripMenuItem_Click);
			// 
			// loadSceneToolStripMenuItem
			// 
			this.loadSceneToolStripMenuItem.Name = "loadSceneToolStripMenuItem";
			this.loadSceneToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
			this.loadSceneToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
			this.loadSceneToolStripMenuItem.Text = "Load";
			this.loadSceneToolStripMenuItem.Click += new System.EventHandler(this.loadSceneToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
			this.exitToolStripMenuItem.Size = new System.Drawing.Size(161, 22);
			this.exitToolStripMenuItem.Text = "Exit";
			this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this.editToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.undoToolStripMenuItem});
			this.editToolStripMenuItem.Name = "editToolStripMenuItem";
			this.editToolStripMenuItem.Size = new System.Drawing.Size(39, 20);
			this.editToolStripMenuItem.Text = "Edit";
			// 
			// undoToolStripMenuItem
			// 
			this.undoToolStripMenuItem.Name = "undoToolStripMenuItem";
			this.undoToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Z)));
			this.undoToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
			this.undoToolStripMenuItem.Text = "Undo";
			this.undoToolStripMenuItem.Click += new System.EventHandler(this.undoToolStripMenuItem_Click);
			// 
			// sceneToolStripMenuItem
			// 
			this.sceneToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newEntityToolStripMenuItem,
            this.importTiledMapToolStripMenuItem});
			this.sceneToolStripMenuItem.Name = "sceneToolStripMenuItem";
			this.sceneToolStripMenuItem.Size = new System.Drawing.Size(50, 20);
			this.sceneToolStripMenuItem.Text = "Scene";
			// 
			// newEntityToolStripMenuItem
			// 
			this.newEntityToolStripMenuItem.Name = "newEntityToolStripMenuItem";
			this.newEntityToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
			this.newEntityToolStripMenuItem.Text = "New entity";
			this.newEntityToolStripMenuItem.ToolTipText = "Add new empty entity without a type.";
			this.newEntityToolStripMenuItem.Click += new System.EventHandler(this.newEntityToolStripMenuItem_Click);
			// 
			// importTiledMapToolStripMenuItem
			// 
			this.importTiledMapToolStripMenuItem.Name = "importTiledMapToolStripMenuItem";
			this.importTiledMapToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
			this.importTiledMapToolStripMenuItem.Text = "Import tiled map...";
			this.importTiledMapToolStripMenuItem.Click += new System.EventHandler(this.importTiledMapToolStripMenuItem_Click);
			// 
			// engineToolStripMenuItem
			// 
			this.engineToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.saveEntityTypesToolStripMenuItem,
            this.compileToolStripMenuItem,
            this.systemListToolStripMenuItem,
            this.statsToolStripMenuItem,
            this.sendCommandToolStripMenuItem,
            this.builddataDirectoryToolStripMenuItem,
            this.openPropellerProfilerDumpToolStripMenuItem});
			this.engineToolStripMenuItem.Name = "engineToolStripMenuItem";
			this.engineToolStripMenuItem.Size = new System.Drawing.Size(55, 20);
			this.engineToolStripMenuItem.Text = "Engine";
			// 
			// saveEntityTypesToolStripMenuItem
			// 
			this.saveEntityTypesToolStripMenuItem.Name = "saveEntityTypesToolStripMenuItem";
			this.saveEntityTypesToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
			this.saveEntityTypesToolStripMenuItem.Text = "Save EntityTypes";
			this.saveEntityTypesToolStripMenuItem.Click += new System.EventHandler(this.saveEntityTypesToolStripMenuItem_Click);
			// 
			// compileToolStripMenuItem
			// 
			this.compileToolStripMenuItem.Name = "compileToolStripMenuItem";
			this.compileToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
			this.compileToolStripMenuItem.Text = "Compile";
			this.compileToolStripMenuItem.Click += new System.EventHandler(this.compileToolStripMenuItem_Click);
			// 
			// systemListToolStripMenuItem
			// 
			this.systemListToolStripMenuItem.Name = "systemListToolStripMenuItem";
			this.systemListToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F7;
			this.systemListToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
			this.systemListToolStripMenuItem.Text = "System List";
			this.systemListToolStripMenuItem.Click += new System.EventHandler(this.systemListToolStripMenuItem_Click);
			// 
			// statsToolStripMenuItem
			// 
			this.statsToolStripMenuItem.Name = "statsToolStripMenuItem";
			this.statsToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F8;
			this.statsToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
			this.statsToolStripMenuItem.Text = "Stats";
			this.statsToolStripMenuItem.Click += new System.EventHandler(this.statsToolStripMenuItem_Click);
			// 
			// sendCommandToolStripMenuItem
			// 
			this.sendCommandToolStripMenuItem.Name = "sendCommandToolStripMenuItem";
			this.sendCommandToolStripMenuItem.ShortcutKeys = System.Windows.Forms.Keys.F9;
			this.sendCommandToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
			this.sendCommandToolStripMenuItem.Text = "Send command...";
			this.sendCommandToolStripMenuItem.Click += new System.EventHandler(this.sendCommandToolStripMenuItem_Click);
			// 
			// builddataDirectoryToolStripMenuItem
			// 
			this.builddataDirectoryToolStripMenuItem.Name = "builddataDirectoryToolStripMenuItem";
			this.builddataDirectoryToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
			this.builddataDirectoryToolStripMenuItem.Text = "Build archives";
			this.builddataDirectoryToolStripMenuItem.Click += new System.EventHandler(this.builddataDirectoryToolStripMenuItem_Click);
			// 
			// dataToolStripMenuItem
			// 
			this.dataToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.import3dModelToolStripMenuItem});
			this.dataToolStripMenuItem.Name = "dataToolStripMenuItem";
			this.dataToolStripMenuItem.Size = new System.Drawing.Size(43, 20);
			this.dataToolStripMenuItem.Text = "Data";
			// 
			// import3dModelToolStripMenuItem
			// 
			this.import3dModelToolStripMenuItem.Name = "import3dModelToolStripMenuItem";
			this.import3dModelToolStripMenuItem.Size = new System.Drawing.Size(163, 22);
			this.import3dModelToolStripMenuItem.Text = "Import 3d model";
			this.import3dModelToolStripMenuItem.Click += new System.EventHandler(this.import3dModelToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this.helpToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.aboutToolStripMenuItem});
			this.helpToolStripMenuItem.Name = "helpToolStripMenuItem";
			this.helpToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
			this.helpToolStripMenuItem.Text = "Help";
			// 
			// aboutToolStripMenuItem
			// 
			this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
			this.aboutToolStripMenuItem.Size = new System.Drawing.Size(107, 22);
			this.aboutToolStripMenuItem.Text = "About";
			this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
			// 
			// statusStrip
			// 
			this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatus});
			this.statusStrip.Location = new System.Drawing.Point(0, 878);
			this.statusStrip.Name = "statusStrip";
			this.statusStrip.Size = new System.Drawing.Size(1387, 22);
			this.statusStrip.TabIndex = 5;
			this.statusStrip.Text = "statusStrip";
			// 
			// toolStripStatus
			// 
			this.toolStripStatus.Name = "toolStripStatus";
			this.toolStripStatus.Size = new System.Drawing.Size(39, 17);
			this.toolStripStatus.Text = "Status";
			// 
			// openPropellerProfilerDumpToolStripMenuItem
			// 
			this.openPropellerProfilerDumpToolStripMenuItem.Name = "openPropellerProfilerDumpToolStripMenuItem";
			this.openPropellerProfilerDumpToolStripMenuItem.Size = new System.Drawing.Size(235, 22);
			this.openPropellerProfilerDumpToolStripMenuItem.Text = "Open PropellerProfiler dump...";
			this.openPropellerProfilerDumpToolStripMenuItem.Click += new System.EventHandler(this.openPropellerProfilerDumpToolStripMenuItem_Click);
			// 
			// MainViewBase
			// 
			this.AllowDrop = true;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1387, 900);
			this.Controls.Add(this.dockPanel);
			this.Controls.Add(this.menuStrip);
			this.Controls.Add(this.statusStrip);
			this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
			this.IsMdiContainer = true;
			this.MainMenuStrip = this.menuStrip;
			this.Name = "MainViewBase";
			this.Text = "PropellerEditor";
			this.menuStrip.ResumeLayout(false);
			this.menuStrip.PerformLayout();
			this.statusStrip.ResumeLayout(false);
			this.statusStrip.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

        }

        #endregion

        private WeifenLuo.WinFormsUI.Docking.DockPanel dockPanel;
        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem engineToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveSceneToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem loadSceneToolStripMenuItem;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatus;
		private System.Windows.Forms.ToolStripMenuItem compileToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem editToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem undoToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem statsToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem saveEntityTypesToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem sendCommandToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem builddataDirectoryToolStripMenuItem;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripMenuItem systemListToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem dataToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem import3dModelToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem sceneToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem newEntityToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem importTiledMapToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem openPropellerProfilerDumpToolStripMenuItem;
    }
}