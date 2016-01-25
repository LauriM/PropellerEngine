namespace Editor.Source_Files.Instances.ModelViewer
{
	partial class ModelViewerView
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
			this.menuStrip1 = new System.Windows.Forms.MenuStrip();
			this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.quitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.modelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.textureToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.viewToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toggleWireframeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.toggleGridToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.renderPanel = new System.Windows.Forms.Panel();
			this.menuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// menuStrip1
			// 
			this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.modelToolStripMenuItem,
            this.viewToolStripMenuItem});
			this.menuStrip1.Location = new System.Drawing.Point(0, 0);
			this.menuStrip1.Name = "menuStrip1";
			this.menuStrip1.Size = new System.Drawing.Size(669, 24);
			this.menuStrip1.TabIndex = 0;
			this.menuStrip1.Text = "menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.quitToolStripMenuItem});
			this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
			this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
			this.fileToolStripMenuItem.Text = "File";
			// 
			// quitToolStripMenuItem
			// 
			this.quitToolStripMenuItem.Name = "quitToolStripMenuItem";
			this.quitToolStripMenuItem.Size = new System.Drawing.Size(97, 22);
			this.quitToolStripMenuItem.Text = "Quit";
			this.quitToolStripMenuItem.Click += new System.EventHandler(this.quitToolStripMenuItem_Click);
			// 
			// modelToolStripMenuItem
			// 
			this.modelToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.textureToolStripMenuItem});
			this.modelToolStripMenuItem.Name = "modelToolStripMenuItem";
			this.modelToolStripMenuItem.Size = new System.Drawing.Size(53, 20);
			this.modelToolStripMenuItem.Text = "Model";
			// 
			// textureToolStripMenuItem
			// 
			this.textureToolStripMenuItem.Name = "textureToolStripMenuItem";
			this.textureToolStripMenuItem.Size = new System.Drawing.Size(113, 22);
			this.textureToolStripMenuItem.Text = "Texture";
			// 
			// viewToolStripMenuItem
			// 
			this.viewToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toggleWireframeToolStripMenuItem,
            this.toggleGridToolStripMenuItem});
			this.viewToolStripMenuItem.Name = "viewToolStripMenuItem";
			this.viewToolStripMenuItem.Size = new System.Drawing.Size(44, 20);
			this.viewToolStripMenuItem.Text = "View";
			// 
			// toggleWireframeToolStripMenuItem
			// 
			this.toggleWireframeToolStripMenuItem.Name = "toggleWireframeToolStripMenuItem";
			this.toggleWireframeToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
			this.toggleWireframeToolStripMenuItem.Text = "Toggle wireframe";
			this.toggleWireframeToolStripMenuItem.Click += new System.EventHandler(this.toggleWireframeToolStripMenuItem_Click);
			// 
			// toggleGridToolStripMenuItem
			// 
			this.toggleGridToolStripMenuItem.Name = "toggleGridToolStripMenuItem";
			this.toggleGridToolStripMenuItem.Size = new System.Drawing.Size(167, 22);
			this.toggleGridToolStripMenuItem.Text = "Toggle grid";
			this.toggleGridToolStripMenuItem.Click += new System.EventHandler(this.toggleGridToolStripMenuItem_Click);
			// 
			// renderPanel
			// 
			this.renderPanel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.renderPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.renderPanel.Location = new System.Drawing.Point(0, 24);
			this.renderPanel.Name = "renderPanel";
			this.renderPanel.Size = new System.Drawing.Size(669, 559);
			this.renderPanel.TabIndex = 1;
			this.renderPanel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.renderPanel_MouseDown);
			this.renderPanel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.renderPanel_MouseMove);
			this.renderPanel.MouseUp += new System.Windows.Forms.MouseEventHandler(this.renderPanel_MouseUp);
			// 
			// ModelViewerView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(669, 583);
			this.Controls.Add(this.renderPanel);
			this.Controls.Add(this.menuStrip1);
			this.MainMenuStrip = this.menuStrip1;
			this.Name = "ModelViewerView";
			this.Text = "ModelViewerView";
			this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ModelViewerView_KeyDown);
			this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.ModelViewerView_KeyUp);
			this.menuStrip1.ResumeLayout(false);
			this.menuStrip1.PerformLayout();
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.MenuStrip menuStrip1;
		private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem quitToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem modelToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem textureToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem viewToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem toggleWireframeToolStripMenuItem;
		public System.Windows.Forms.Panel renderPanel;
		private System.Windows.Forms.ToolStripMenuItem toggleGridToolStripMenuItem;
	}
}