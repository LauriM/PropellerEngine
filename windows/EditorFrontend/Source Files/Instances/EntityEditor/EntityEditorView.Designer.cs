namespace Editor.Source_Files.Views
{
	partial class EntityEditorView
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
			this.nameBox = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.splitContainer = new System.Windows.Forms.SplitContainer();
			this.typeTextBox = new System.Windows.Forms.TextBox();
			this.typeLabel = new System.Windows.Forms.Label();
			this.addComponentButton = new System.Windows.Forms.Button();
			this.componentAddComboBox = new System.Windows.Forms.ComboBox();
			this.componentTreeView = new System.Windows.Forms.TreeView();
			this.componentContextMenu = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.editComponentSourceButton = new System.Windows.Forms.ToolStripMenuItem();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer)).BeginInit();
			this.splitContainer.Panel1.SuspendLayout();
			this.splitContainer.Panel2.SuspendLayout();
			this.splitContainer.SuspendLayout();
			this.componentContextMenu.SuspendLayout();
			this.SuspendLayout();
			// 
			// nameBox
			// 
			this.nameBox.Location = new System.Drawing.Point(54, 9);
			this.nameBox.Name = "nameBox";
			this.nameBox.Size = new System.Drawing.Size(100, 20);
			this.nameBox.TabIndex = 0;
			this.nameBox.KeyUp += new System.Windows.Forms.KeyEventHandler(this.nameBox_KeyUp);
			this.nameBox.Leave += new System.EventHandler(this.nameBox_Leave);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point(13, 12);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(35, 13);
			this.label1.TabIndex = 1;
			this.label1.Text = "Name";
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
			this.splitContainer.Panel1.Controls.Add(this.typeTextBox);
			this.splitContainer.Panel1.Controls.Add(this.typeLabel);
			this.splitContainer.Panel1.Controls.Add(this.addComponentButton);
			this.splitContainer.Panel1.Controls.Add(this.componentAddComboBox);
			this.splitContainer.Panel1.Controls.Add(this.label1);
			this.splitContainer.Panel1.Controls.Add(this.nameBox);
			this.splitContainer.Panel1MinSize = 65;
			// 
			// splitContainer.Panel2
			// 
			this.splitContainer.Panel2.Controls.Add(this.componentTreeView);
			this.splitContainer.Size = new System.Drawing.Size(335, 444);
			this.splitContainer.SplitterDistance = 65;
			this.splitContainer.TabIndex = 0;
			// 
			// typeTextBox
			// 
			this.typeTextBox.Location = new System.Drawing.Point(197, 8);
			this.typeTextBox.Name = "typeTextBox";
			this.typeTextBox.ReadOnly = true;
			this.typeTextBox.Size = new System.Drawing.Size(126, 20);
			this.typeTextBox.TabIndex = 5;
			this.typeTextBox.Visible = false;
			// 
			// typeLabel
			// 
			this.typeLabel.AutoSize = true;
			this.typeLabel.Location = new System.Drawing.Point(160, 12);
			this.typeLabel.Name = "typeLabel";
			this.typeLabel.Size = new System.Drawing.Size(31, 13);
			this.typeLabel.TabIndex = 4;
			this.typeLabel.Text = "Type";
			this.typeLabel.Visible = false;
			// 
			// addComponentButton
			// 
			this.addComponentButton.Location = new System.Drawing.Point(160, 33);
			this.addComponentButton.Name = "addComponentButton";
			this.addComponentButton.Size = new System.Drawing.Size(92, 23);
			this.addComponentButton.TabIndex = 3;
			this.addComponentButton.Text = "Add component";
			this.addComponentButton.UseVisualStyleBackColor = true;
			this.addComponentButton.Click += new System.EventHandler(this.addComponentButton_Click);
			// 
			// componentAddComboBox
			// 
			this.componentAddComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.componentAddComboBox.FormattingEnabled = true;
			this.componentAddComboBox.Location = new System.Drawing.Point(16, 35);
			this.componentAddComboBox.Name = "componentAddComboBox";
			this.componentAddComboBox.Size = new System.Drawing.Size(138, 21);
			this.componentAddComboBox.TabIndex = 2;
			// 
			// componentTreeView
			// 
			this.componentTreeView.Dock = System.Windows.Forms.DockStyle.Fill;
			this.componentTreeView.Location = new System.Drawing.Point(0, 0);
			this.componentTreeView.Name = "componentTreeView";
			this.componentTreeView.Size = new System.Drawing.Size(335, 375);
			this.componentTreeView.TabIndex = 0;
			this.componentTreeView.KeyDown += new System.Windows.Forms.KeyEventHandler(this.componentTreeView_KeyDown);
			this.componentTreeView.MouseUp += new System.Windows.Forms.MouseEventHandler(this.componentTreeView_MouseUp_1);
			// 
			// componentContextMenu
			// 
			this.componentContextMenu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.editComponentSourceButton});
			this.componentContextMenu.Name = "componentContextMenu";
			this.componentContextMenu.Size = new System.Drawing.Size(133, 26);
			// 
			// editComponentSourceButton
			// 
			this.editComponentSourceButton.Name = "editComponentSourceButton";
			this.editComponentSourceButton.Size = new System.Drawing.Size(132, 22);
			this.editComponentSourceButton.Text = "Edit source";
			this.editComponentSourceButton.Click += new System.EventHandler(this.editComponentSourceButton_Click);
			// 
			// EntityEditorView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(335, 444);
			this.Controls.Add(this.splitContainer);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "EntityEditorView";
			this.Text = "Entity Editor";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.TypeEditorView_FormClosed);
			this.splitContainer.Panel1.ResumeLayout(false);
			this.splitContainer.Panel1.PerformLayout();
			this.splitContainer.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer)).EndInit();
			this.splitContainer.ResumeLayout(false);
			this.componentContextMenu.ResumeLayout(false);
			this.ResumeLayout(false);

		}

		#endregion

		public System.Windows.Forms.TextBox nameBox;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.SplitContainer splitContainer;
		private System.Windows.Forms.TreeView componentTreeView;
		private System.Windows.Forms.Button addComponentButton;
		private System.Windows.Forms.ComboBox componentAddComboBox;
		private System.Windows.Forms.TextBox typeTextBox;
		private System.Windows.Forms.Label typeLabel;
		private System.Windows.Forms.ContextMenuStrip componentContextMenu;
		private System.Windows.Forms.ToolStripMenuItem editComponentSourceButton;


	}
}