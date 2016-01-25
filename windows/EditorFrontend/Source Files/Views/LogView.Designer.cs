namespace Editor.Source_Files.Views
{
    partial class LogView
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
			this.logTextBox = new System.Windows.Forms.RichTextBox();
			this.SuspendLayout();
			// 
			// logTextBox
			// 
			this.logTextBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.logTextBox.Location = new System.Drawing.Point(0, 0);
			this.logTextBox.Name = "logTextBox";
			this.logTextBox.ReadOnly = true;
			this.logTextBox.Size = new System.Drawing.Size(485, 239);
			this.logTextBox.TabIndex = 0;
			this.logTextBox.Text = "";
			// 
			// LogView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(485, 239);
			this.Controls.Add(this.logTextBox);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "LogView";
			this.Text = "LogView";
			this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.LogView_FormClosing);
			this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RichTextBox logTextBox;
    }
}