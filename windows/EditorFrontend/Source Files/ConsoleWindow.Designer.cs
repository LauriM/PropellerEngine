namespace Editor.Source_Files
{
    partial class ConsoleWindow
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
            this.cmdTextBox = new System.Windows.Forms.TextBox();
            this.sendCmdButton = new System.Windows.Forms.Button();
            this.outputListBox = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // cmdTextBox
            // 
            this.cmdTextBox.Location = new System.Drawing.Point(13, 374);
            this.cmdTextBox.Name = "cmdTextBox";
            this.cmdTextBox.Size = new System.Drawing.Size(465, 20);
            this.cmdTextBox.TabIndex = 0;
            // 
            // sendCmdButton
            // 
            this.sendCmdButton.Location = new System.Drawing.Point(485, 371);
            this.sendCmdButton.Name = "sendCmdButton";
            this.sendCmdButton.Size = new System.Drawing.Size(75, 23);
            this.sendCmdButton.TabIndex = 1;
            this.sendCmdButton.Text = "Send";
            this.sendCmdButton.UseVisualStyleBackColor = true;
            // 
            // outputListBox
            // 
            this.outputListBox.FormattingEnabled = true;
            this.outputListBox.Location = new System.Drawing.Point(13, 13);
            this.outputListBox.Name = "outputListBox";
            this.outputListBox.Size = new System.Drawing.Size(541, 342);
            this.outputListBox.TabIndex = 2;
            // 
            // ConsoleWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(566, 406);
            this.Controls.Add(this.outputListBox);
            this.Controls.Add(this.sendCmdButton);
            this.Controls.Add(this.cmdTextBox);
            this.Name = "ConsoleWindow";
            this.Text = "ConsoleWindow";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox cmdTextBox;
        private System.Windows.Forms.Button sendCmdButton;
        private System.Windows.Forms.ListBox outputListBox;
    }
}