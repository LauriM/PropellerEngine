namespace Editor.Source_Files
{
    partial class EditorView
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(EditorView));
			this.BottomToolStripPanel = new System.Windows.Forms.ToolStripPanel();
			this.TopToolStripPanel = new System.Windows.Forms.ToolStripPanel();
			this.RightToolStripPanel = new System.Windows.Forms.ToolStripPanel();
			this.LeftToolStripPanel = new System.Windows.Forms.ToolStripPanel();
			this.ContentPanel = new System.Windows.Forms.ToolStripContentPanel();
			this.splitContainer = new System.Windows.Forms.SplitContainer();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.openButton = new System.Windows.Forms.ToolStripButton();
			this.saveButton = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.toggle2d3dbutton = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
			this.playButton = new System.Windows.Forms.ToolStripButton();
			this.pauseButton = new System.Windows.Forms.ToolStripButton();
			this.stopButton = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
			this.launchGame = new System.Windows.Forms.ToolStripButton();
			this.instanceViewPanel = new System.Windows.Forms.Panel();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer)).BeginInit();
			this.splitContainer.Panel1.SuspendLayout();
			this.splitContainer.Panel2.SuspendLayout();
			this.splitContainer.SuspendLayout();
			this.toolStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// BottomToolStripPanel
			// 
			this.BottomToolStripPanel.Location = new System.Drawing.Point(0, 0);
			this.BottomToolStripPanel.Name = "BottomToolStripPanel";
			this.BottomToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
			this.BottomToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
			this.BottomToolStripPanel.Size = new System.Drawing.Size(0, 0);
			// 
			// TopToolStripPanel
			// 
			this.TopToolStripPanel.Location = new System.Drawing.Point(0, 0);
			this.TopToolStripPanel.Name = "TopToolStripPanel";
			this.TopToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
			this.TopToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
			this.TopToolStripPanel.Size = new System.Drawing.Size(0, 0);
			// 
			// RightToolStripPanel
			// 
			this.RightToolStripPanel.Location = new System.Drawing.Point(0, 0);
			this.RightToolStripPanel.Name = "RightToolStripPanel";
			this.RightToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
			this.RightToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
			this.RightToolStripPanel.Size = new System.Drawing.Size(0, 0);
			// 
			// LeftToolStripPanel
			// 
			this.LeftToolStripPanel.Location = new System.Drawing.Point(0, 0);
			this.LeftToolStripPanel.Name = "LeftToolStripPanel";
			this.LeftToolStripPanel.Orientation = System.Windows.Forms.Orientation.Horizontal;
			this.LeftToolStripPanel.RowMargin = new System.Windows.Forms.Padding(3, 0, 0, 0);
			this.LeftToolStripPanel.Size = new System.Drawing.Size(0, 0);
			// 
			// ContentPanel
			// 
			this.ContentPanel.AutoScroll = true;
			this.ContentPanel.Size = new System.Drawing.Size(942, 701);
			// 
			// splitContainer
			// 
			this.splitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer.Location = new System.Drawing.Point(0, 0);
			this.splitContainer.Name = "splitContainer";
			this.splitContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// splitContainer.Panel1
			// 
			this.splitContainer.Panel1.Controls.Add(this.toolStrip1);
			// 
			// splitContainer.Panel2
			// 
			this.splitContainer.Panel2.Controls.Add(this.instanceViewPanel);
			this.splitContainer.Size = new System.Drawing.Size(942, 726);
			this.splitContainer.SplitterDistance = 25;
			this.splitContainer.TabIndex = 0;
			this.splitContainer.KeyDown += new System.Windows.Forms.KeyEventHandler(this.EditorView_KeyDown);
			this.splitContainer.KeyUp += new System.Windows.Forms.KeyEventHandler(this.EditorView_KeyUp);
			// 
			// toolStrip1
			// 
			this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openButton,
            this.saveButton,
            this.toolStripSeparator1,
            this.toggle2d3dbutton,
            this.toolStripSeparator2,
            this.playButton,
            this.pauseButton,
            this.stopButton,
            this.toolStripSeparator3,
            this.launchGame});
			this.toolStrip1.Location = new System.Drawing.Point(0, 0);
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size(942, 25);
			this.toolStrip1.TabIndex = 0;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// openButton
			// 
			this.openButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.openButton.Image = ((System.Drawing.Image)(resources.GetObject("openButton.Image")));
			this.openButton.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.openButton.Name = "openButton";
			this.openButton.Size = new System.Drawing.Size(23, 22);
			this.openButton.Text = "Open scene";
			this.openButton.Click += new System.EventHandler(this.openButton_Click);
			// 
			// saveButton
			// 
			this.saveButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.saveButton.Image = ((System.Drawing.Image)(resources.GetObject("saveButton.Image")));
			this.saveButton.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.saveButton.Name = "saveButton";
			this.saveButton.Size = new System.Drawing.Size(23, 22);
			this.saveButton.Text = "Save scene";
			this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
			// 
			// toggle2d3dbutton
			// 
			this.toggle2d3dbutton.Image = ((System.Drawing.Image)(resources.GetObject("toggle2d3dbutton.Image")));
			this.toggle2d3dbutton.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toggle2d3dbutton.Name = "toggle2d3dbutton";
			this.toggle2d3dbutton.Size = new System.Drawing.Size(140, 22);
			this.toggle2d3dbutton.Text = "Toggle 2D / 3D mode";
			this.toggle2d3dbutton.Click += new System.EventHandler(this.toggle2d3dbutton_Click);
			// 
			// toolStripSeparator2
			// 
			this.toolStripSeparator2.Name = "toolStripSeparator2";
			this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
			// 
			// playButton
			// 
			this.playButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.playButton.Image = ((System.Drawing.Image)(resources.GetObject("playButton.Image")));
			this.playButton.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.playButton.Name = "playButton";
			this.playButton.Size = new System.Drawing.Size(23, 22);
			this.playButton.Text = "Run the game";
			this.playButton.Click += new System.EventHandler(this.playButton_Click);
			// 
			// pauseButton
			// 
			this.pauseButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.pauseButton.Image = ((System.Drawing.Image)(resources.GetObject("pauseButton.Image")));
			this.pauseButton.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.pauseButton.Name = "pauseButton";
			this.pauseButton.Size = new System.Drawing.Size(23, 22);
			this.pauseButton.Text = "Pause the simulation";
			this.pauseButton.Click += new System.EventHandler(this.pauseButton_Click);
			// 
			// stopButton
			// 
			this.stopButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.stopButton.Image = ((System.Drawing.Image)(resources.GetObject("stopButton.Image")));
			this.stopButton.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.stopButton.Name = "stopButton";
			this.stopButton.Size = new System.Drawing.Size(23, 22);
			this.stopButton.Text = "Stop the engine";
			this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
			// 
			// toolStripSeparator3
			// 
			this.toolStripSeparator3.Name = "toolStripSeparator3";
			this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
			// 
			// launchGame
			// 
			this.launchGame.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.launchGame.Image = ((System.Drawing.Image)(resources.GetObject("launchGame.Image")));
			this.launchGame.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.launchGame.Name = "launchGame";
			this.launchGame.Size = new System.Drawing.Size(23, 22);
			this.launchGame.Text = "Launch the game in a separate window (more stable)";
			this.launchGame.Click += new System.EventHandler(this.launchGame_Click);
			// 
			// instanceViewPanel
			// 
			this.instanceViewPanel.AllowDrop = true;
			this.instanceViewPanel.BackColor = System.Drawing.SystemColors.Desktop;
			this.instanceViewPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.instanceViewPanel.Location = new System.Drawing.Point(0, 0);
			this.instanceViewPanel.Name = "instanceViewPanel";
			this.instanceViewPanel.Size = new System.Drawing.Size(942, 697);
			this.instanceViewPanel.TabIndex = 1;
			this.instanceViewPanel.TabStop = true;
			this.instanceViewPanel.DragDrop += new System.Windows.Forms.DragEventHandler(this.instanceViewPanel_DragDrop);
			this.instanceViewPanel.DragOver += new System.Windows.Forms.DragEventHandler(this.instanceViewPanel_DragOver);
			this.instanceViewPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.instanceViewPanel_MouseDown);
			this.instanceViewPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.instanceViewPanel_MouseMove);
			this.instanceViewPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.instanceViewPanel_MouseUp);
			// 
			// EditorView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(942, 726);
			this.Controls.Add(this.splitContainer);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "EditorView";
			this.Text = "Editor";
			this.splitContainer.Panel1.ResumeLayout(false);
			this.splitContainer.Panel1.PerformLayout();
			this.splitContainer.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer)).EndInit();
			this.splitContainer.ResumeLayout(false);
			this.toolStrip1.ResumeLayout(false);
			this.toolStrip1.PerformLayout();
			this.ResumeLayout(false);

        }

        #endregion

		private System.Windows.Forms.ToolStripPanel BottomToolStripPanel;
		private System.Windows.Forms.ToolStripPanel TopToolStripPanel;
		private System.Windows.Forms.ToolStripPanel RightToolStripPanel;
		private System.Windows.Forms.ToolStripPanel LeftToolStripPanel;
		private System.Windows.Forms.ToolStripContentPanel ContentPanel;
		private System.Windows.Forms.SplitContainer splitContainer;
		public System.Windows.Forms.Panel instanceViewPanel;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripButton openButton;
		private System.Windows.Forms.ToolStripButton saveButton;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripButton toggle2d3dbutton;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripButton playButton;
		private System.Windows.Forms.ToolStripButton pauseButton;
		private System.Windows.Forms.ToolStripButton stopButton;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
		private System.Windows.Forms.ToolStripButton launchGame;



	}
}