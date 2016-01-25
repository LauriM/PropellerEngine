namespace Editor.Source_Files.Instances.Stats
{
	partial class StatsView
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
			System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
			System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
			System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.splitContainer2 = new System.Windows.Forms.SplitContainer();
			this.clearButton = new System.Windows.Forms.Button();
			this.resetButton = new System.Windows.Forms.Button();
			this.dataSelectionBox = new System.Windows.Forms.CheckedListBox();
			this.chart = new System.Windows.Forms.DataVisualization.Charting.Chart();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
			this.splitContainer2.Panel1.SuspendLayout();
			this.splitContainer2.Panel2.SuspendLayout();
			this.splitContainer2.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.chart)).BeginInit();
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
			this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add(this.chart);
			this.splitContainer1.Size = new System.Drawing.Size(1191, 582);
			this.splitContainer1.SplitterDistance = 188;
			this.splitContainer1.TabIndex = 0;
			// 
			// splitContainer2
			// 
			this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer2.Location = new System.Drawing.Point(0, 0);
			this.splitContainer2.Name = "splitContainer2";
			this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
			// 
			// splitContainer2.Panel1
			// 
			this.splitContainer2.Panel1.AutoScroll = true;
			this.splitContainer2.Panel1.Controls.Add(this.clearButton);
			this.splitContainer2.Panel1.Controls.Add(this.resetButton);
			// 
			// splitContainer2.Panel2
			// 
			this.splitContainer2.Panel2.Controls.Add(this.dataSelectionBox);
			this.splitContainer2.Size = new System.Drawing.Size(188, 582);
			this.splitContainer2.SplitterDistance = 67;
			this.splitContainer2.TabIndex = 1;
			// 
			// clearButton
			// 
			this.clearButton.Location = new System.Drawing.Point(94, 13);
			this.clearButton.Name = "clearButton";
			this.clearButton.Size = new System.Drawing.Size(75, 23);
			this.clearButton.TabIndex = 1;
			this.clearButton.Text = "Clear";
			this.clearButton.UseVisualStyleBackColor = true;
			this.clearButton.Click += new System.EventHandler(this.clearButton_Click);
			// 
			// resetButton
			// 
			this.resetButton.Location = new System.Drawing.Point(13, 13);
			this.resetButton.Name = "resetButton";
			this.resetButton.Size = new System.Drawing.Size(75, 23);
			this.resetButton.TabIndex = 0;
			this.resetButton.Text = "Reset";
			this.resetButton.UseVisualStyleBackColor = true;
			this.resetButton.Click += new System.EventHandler(this.resetButton_Click);
			// 
			// dataSelectionBox
			// 
			this.dataSelectionBox.Dock = System.Windows.Forms.DockStyle.Fill;
			this.dataSelectionBox.FormattingEnabled = true;
			this.dataSelectionBox.Location = new System.Drawing.Point(0, 0);
			this.dataSelectionBox.Name = "dataSelectionBox";
			this.dataSelectionBox.Size = new System.Drawing.Size(188, 511);
			this.dataSelectionBox.TabIndex = 0;
			this.dataSelectionBox.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.dataSelectionBox_ItemCheck);
			// 
			// chart
			// 
			chartArea3.Name = "ChartArea1";
			this.chart.ChartAreas.Add(chartArea3);
			this.chart.Dock = System.Windows.Forms.DockStyle.Fill;
			legend3.Name = "Legend1";
			this.chart.Legends.Add(legend3);
			this.chart.Location = new System.Drawing.Point(0, 0);
			this.chart.Name = "chart";
			series3.ChartArea = "ChartArea1";
			series3.Legend = "Legend1";
			series3.Name = "Series1";
			this.chart.Series.Add(series3);
			this.chart.Size = new System.Drawing.Size(999, 582);
			this.chart.TabIndex = 0;
			this.chart.Text = "chart";
			// 
			// StatsView
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1191, 582);
			this.Controls.Add(this.splitContainer1);
			this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.Name = "StatsView";
			this.Text = "StatsView";
			this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.StatsView_FormClosed);
			this.splitContainer1.Panel1.ResumeLayout(false);
			this.splitContainer1.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
			this.splitContainer1.ResumeLayout(false);
			this.splitContainer2.Panel1.ResumeLayout(false);
			this.splitContainer2.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
			this.splitContainer2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)(this.chart)).EndInit();
			this.ResumeLayout(false);

		}

		#endregion

		private System.Windows.Forms.SplitContainer splitContainer1;
		private System.Windows.Forms.DataVisualization.Charting.Chart chart;
		private System.Windows.Forms.SplitContainer splitContainer2;
		private System.Windows.Forms.CheckedListBox dataSelectionBox;
		private System.Windows.Forms.Button clearButton;
		private System.Windows.Forms.Button resetButton;
	}
}