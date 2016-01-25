namespace Editor.Source_Files.Instances.SystemList
{
	partial class SystemListView
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
			this.systemListBox = new System.Windows.Forms.CheckedListBox();
			this.SuspendLayout();
			// 
			// systemListBox
			// 
			this.systemListBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.systemListBox.FormattingEnabled = true;
			this.systemListBox.Location = new System.Drawing.Point(0, 0);
			this.systemListBox.Name = "systemListBox";
			this.systemListBox.Size = new System.Drawing.Size(573, 241);
			this.systemListBox.TabIndex = 0;
			// 
			// SystemListView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(573, 241);
			this.Controls.Add(this.systemListBox);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "SystemListView";
			this.Text = "SystemListView";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.SystemListView_FormClosed);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.CheckedListBox systemListBox;
	}
}