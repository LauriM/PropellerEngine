namespace Editor.Source_Files.Views
{
	partial class UndoListView
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
			this.undoList = new System.Windows.Forms.ListBox();
			this.SuspendLayout();
			// 
			// undoList
			// 
			this.undoList.Dock = System.Windows.Forms.DockStyle.Fill;
			this.undoList.FormattingEnabled = true;
			this.undoList.Location = new System.Drawing.Point(0, 0);
			this.undoList.Name = "undoList";
			this.undoList.Size = new System.Drawing.Size(297, 450);
			this.undoList.TabIndex = 0;
			// 
			// UndoListView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(297, 450);
			this.Controls.Add(this.undoList);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "UndoListView";
			this.Text = "Undo History";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.UndoListView_FormClosing);
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.ListBox undoList;
	}
}