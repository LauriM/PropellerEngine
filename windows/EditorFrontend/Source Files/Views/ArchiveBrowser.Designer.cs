namespace Editor.Source_Files.Views
{
    partial class ArchiveBrowser
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
			this.components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ArchiveBrowser));
			this.archiveImageList = new System.Windows.Forms.ImageList(this.components);
			this.contextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.toolStripMenuItemCreateEntity = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.toolStripMenuItemDelete = new System.Windows.Forms.ToolStripMenuItem();
			this.archiveSplitter = new System.Windows.Forms.SplitContainer();
			this.fileCountLabel = new System.Windows.Forms.Label();
			this.refreshButton = new System.Windows.Forms.Button();
			this.treeView = new System.Windows.Forms.TreeView();
			this.contextMenu.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.archiveSplitter)).BeginInit();
			this.archiveSplitter.Panel1.SuspendLayout();
			this.archiveSplitter.Panel2.SuspendLayout();
			this.archiveSplitter.SuspendLayout();
			this.SuspendLayout();
			// 
			// archiveImageList
			// 
			this.archiveImageList.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("archiveImageList.ImageStream")));
			this.archiveImageList.TransparentColor = System.Drawing.Color.Transparent;
			this.archiveImageList.Images.SetKeyName(0, "propelli.ico");
			this.archiveImageList.Images.SetKeyName(1, "json.png");
			this.archiveImageList.Images.SetKeyName(2, "png.png");
			// 
			// contextMenu
			// 
			this.contextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItemCreateEntity,
            this.toolStripSeparator1,
            this.toolStripMenuItemDelete});
			this.contextMenu.Name = "contextMenu";
			this.contextMenu.Size = new System.Drawing.Size(211, 54);
			// 
			// toolStripMenuItemCreateEntity
			// 
			this.toolStripMenuItemCreateEntity.Name = "toolStripMenuItemCreateEntity";
			this.toolStripMenuItemCreateEntity.Size = new System.Drawing.Size(210, 22);
			this.toolStripMenuItemCreateEntity.Text = "Create entity type";
			this.toolStripMenuItemCreateEntity.Click += new System.EventHandler(this.toolStripMenuItemCreateEntity_Click);
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size(207, 6);
			// 
			// toolStripMenuItemDelete
			// 
			this.toolStripMenuItemDelete.Name = "toolStripMenuItemDelete";
			this.toolStripMenuItemDelete.Size = new System.Drawing.Size(210, 22);
			this.toolStripMenuItemDelete.Text = "Delete (not implemented)";
			// 
			// archiveSplitter
			// 
			this.archiveSplitter.Dock = System.Windows.Forms.DockStyle.Fill;
			this.archiveSplitter.FixedPanel = System.Windows.Forms.FixedPanel.Panel1;
			this.archiveSplitter.IsSplitterFixed = true;
			this.archiveSplitter.Location = new System.Drawing.Point(0, 0);
			this.archiveSplitter.Name = "archiveSplitter";
			this.archiveSplitter.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// archiveSplitter.Panel1
			// 
			this.archiveSplitter.Panel1.Controls.Add(this.fileCountLabel);
			this.archiveSplitter.Panel1.Controls.Add(this.refreshButton);
			// 
			// archiveSplitter.Panel2
			// 
			this.archiveSplitter.Panel2.Controls.Add(this.treeView);
			this.archiveSplitter.Size = new System.Drawing.Size(308, 289);
			this.archiveSplitter.SplitterDistance = 25;
			this.archiveSplitter.TabIndex = 1;
			// 
			// fileCountLabel
			// 
			this.fileCountLabel.AutoSize = true;
			this.fileCountLabel.Location = new System.Drawing.Point(139, 9);
			this.fileCountLabel.Name = "fileCountLabel";
			this.fileCountLabel.Size = new System.Drawing.Size(73, 13);
			this.fileCountLabel.TabIndex = 1;
			this.fileCountLabel.Text = "Total of ? files";
			// 
			// refreshButton
			// 
			this.refreshButton.Location = new System.Drawing.Point(3, 3);
			this.refreshButton.Name = "refreshButton";
			this.refreshButton.Size = new System.Drawing.Size(129, 23);
			this.refreshButton.TabIndex = 0;
			this.refreshButton.Text = "Refresh";
			this.refreshButton.UseVisualStyleBackColor = true;
			this.refreshButton.Click += new System.EventHandler(this.refreshButton_Click);
			// 
			// treeView
			// 
			this.treeView.AllowDrop = true;
			this.treeView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.treeView.ImageIndex = 0;
			this.treeView.ImageList = this.archiveImageList;
			this.treeView.Location = new System.Drawing.Point(0, 0);
			this.treeView.Name = "treeView";
			this.treeView.SelectedImageIndex = 0;
			this.treeView.Size = new System.Drawing.Size(308, 260);
			this.treeView.TabIndex = 1;
			this.treeView.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.treeView_DoubleClick);
			this.treeView.MouseLeave += new System.EventHandler(this.treeView_MouseLeave);
			this.treeView.MouseUp += new System.Windows.Forms.MouseEventHandler(this.treeView_MouseUp);
			// 
			// ArchiveBrowser
			// 
			this.AllowDrop = true;
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(308, 289);
			this.Controls.Add(this.archiveSplitter);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "ArchiveBrowser";
			this.Text = "Archive Browser";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.ArchiveBrowser_FormClosing);
			this.contextMenu.ResumeLayout(false);
			this.archiveSplitter.Panel1.ResumeLayout(false);
			this.archiveSplitter.Panel1.PerformLayout();
			this.archiveSplitter.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.archiveSplitter)).EndInit();
			this.archiveSplitter.ResumeLayout(false);
			this.ResumeLayout(false);

        }

        #endregion

		private System.Windows.Forms.ImageList archiveImageList;
		private System.Windows.Forms.ContextMenuStrip contextMenu;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemCreateEntity;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripMenuItem toolStripMenuItemDelete;
		private System.Windows.Forms.SplitContainer archiveSplitter;
		private System.Windows.Forms.Button refreshButton;
		private System.Windows.Forms.TreeView treeView;
		private System.Windows.Forms.Label fileCountLabel;

	}
}