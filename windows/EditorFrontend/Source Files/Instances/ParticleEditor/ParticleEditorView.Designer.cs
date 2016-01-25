namespace Editor.Source_Files.Instances.ParticleEditor
{
	partial class ParticleEditorView
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
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.renderPanel = new System.Windows.Forms.Panel();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.SuspendLayout();
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point(0, 0);
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add(this.renderPanel);
			this.splitContainer1.Size = new System.Drawing.Size(544, 501);
			this.splitContainer1.SplitterDistance = 404;
			this.splitContainer1.TabIndex = 0;
			// 
			// renderPanel
			// 
			this.renderPanel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
			this.renderPanel.Dock = System.Windows.Forms.DockStyle.Fill;
			this.renderPanel.Location = new System.Drawing.Point(0, 0);
			this.renderPanel.Name = "renderPanel";
			this.renderPanel.Size = new System.Drawing.Size(404, 501);
			this.renderPanel.TabIndex = 0;
			// 
			// EffectsEditorView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(544, 501);
			this.Controls.Add(this.splitContainer1);
			this.Name = "EffectsEditorView";
			this.Text = "EffectsEditorView";
			this.splitContainer1.Panel1.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
			this.splitContainer1.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.SplitContainer splitContainer1;
		public System.Windows.Forms.Panel renderPanel;
	}
}