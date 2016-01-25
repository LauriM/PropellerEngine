namespace Editor.Source_Files.Helpers
{
	partial class TextInputDialog
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
			this.textBox = new System.Windows.Forms.TextBox();
			this.okButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox
			// 
			this.textBox.Location = new System.Drawing.Point(13, 13);
			this.textBox.Name = "textBox";
			this.textBox.Size = new System.Drawing.Size(226, 20);
			this.textBox.TabIndex = 0;
			this.textBox.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textBox_KeyUp);
			// 
			// okButton
			// 
			this.okButton.Location = new System.Drawing.Point(246, 9);
			this.okButton.Name = "okButton";
			this.okButton.Size = new System.Drawing.Size(75, 23);
			this.okButton.TabIndex = 1;
			this.okButton.Text = "Ok";
			this.okButton.UseVisualStyleBackColor = true;
			this.okButton.Click += new System.EventHandler(this.okButton_Click);
			// 
			// TextInputDialog
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(329, 46);
			this.Controls.Add(this.okButton);
			this.Controls.Add(this.textBox);
			this.Name = "TextInputDialog";
			this.Text = "TextInput";
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button okButton;
		private System.Windows.Forms.TextBox textBox;
	}
}