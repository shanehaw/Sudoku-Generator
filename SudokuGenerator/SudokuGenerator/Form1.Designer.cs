namespace SudokuGenerator
{
    partial class frmSudokuGenerator
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmSudokuGenerator));
            this.tbNumOfPuzzles = new System.Windows.Forms.TextBox();
            this.lblNumOfPuzzles = new System.Windows.Forms.Label();
            this.rbEasy = new System.Windows.Forms.RadioButton();
            this.rbIntemediate = new System.Windows.Forms.RadioButton();
            this.tbOutputFileLocation = new System.Windows.Forms.TextBox();
            this.lblOutputFileTo = new System.Windows.Forms.Label();
            this.fbdOutputFile = new System.Windows.Forms.FolderBrowserDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.tbNameOfOutputFile = new System.Windows.Forms.TextBox();
            this.btnGenerate = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // tbNumOfPuzzles
            // 
            this.tbNumOfPuzzles.Location = new System.Drawing.Point(165, 100);
            this.tbNumOfPuzzles.Margin = new System.Windows.Forms.Padding(4);
            this.tbNumOfPuzzles.Name = "tbNumOfPuzzles";
            this.tbNumOfPuzzles.Size = new System.Drawing.Size(189, 26);
            this.tbNumOfPuzzles.TabIndex = 0;
            this.tbNumOfPuzzles.Text = "0";
            // 
            // lblNumOfPuzzles
            // 
            this.lblNumOfPuzzles.Location = new System.Drawing.Point(13, 103);
            this.lblNumOfPuzzles.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblNumOfPuzzles.Name = "lblNumOfPuzzles";
            this.lblNumOfPuzzles.Size = new System.Drawing.Size(107, 24);
            this.lblNumOfPuzzles.TabIndex = 1;
            this.lblNumOfPuzzles.Text = "Num of Puzzles";
            // 
            // rbEasy
            // 
            this.rbEasy.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.rbEasy.Checked = true;
            this.rbEasy.Location = new System.Drawing.Point(13, 141);
            this.rbEasy.Margin = new System.Windows.Forms.Padding(4);
            this.rbEasy.Name = "rbEasy";
            this.rbEasy.Size = new System.Drawing.Size(164, 24);
            this.rbEasy.TabIndex = 2;
            this.rbEasy.TabStop = true;
            this.rbEasy.Text = "Easy";
            this.rbEasy.UseVisualStyleBackColor = true;
            // 
            // rbIntemediate
            // 
            this.rbIntemediate.CheckAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.rbIntemediate.Location = new System.Drawing.Point(13, 179);
            this.rbIntemediate.Margin = new System.Windows.Forms.Padding(4);
            this.rbIntemediate.Name = "rbIntemediate";
            this.rbIntemediate.Size = new System.Drawing.Size(164, 24);
            this.rbIntemediate.TabIndex = 3;
            this.rbIntemediate.Text = "Intemediate";
            this.rbIntemediate.UseVisualStyleBackColor = true;
            // 
            // tbOutputFileLocation
            // 
            this.tbOutputFileLocation.Enabled = false;
            this.tbOutputFileLocation.Location = new System.Drawing.Point(165, 24);
            this.tbOutputFileLocation.Margin = new System.Windows.Forms.Padding(4);
            this.tbOutputFileLocation.Name = "tbOutputFileLocation";
            this.tbOutputFileLocation.Size = new System.Drawing.Size(468, 26);
            this.tbOutputFileLocation.TabIndex = 4;
            this.tbOutputFileLocation.Text = "C:\\";
            // 
            // lblOutputFileTo
            // 
            this.lblOutputFileTo.Location = new System.Drawing.Point(13, 27);
            this.lblOutputFileTo.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblOutputFileTo.Name = "lblOutputFileTo";
            this.lblOutputFileTo.Size = new System.Drawing.Size(144, 24);
            this.lblOutputFileTo.TabIndex = 5;
            this.lblOutputFileTo.Text = "Output File Location:";
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(13, 65);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(144, 24);
            this.label1.TabIndex = 7;
            this.label1.Text = "Name of Output File:";
            // 
            // tbNameOfOutputFile
            // 
            this.tbNameOfOutputFile.Location = new System.Drawing.Point(165, 62);
            this.tbNameOfOutputFile.Margin = new System.Windows.Forms.Padding(4);
            this.tbNameOfOutputFile.Name = "tbNameOfOutputFile";
            this.tbNameOfOutputFile.Size = new System.Drawing.Size(189, 26);
            this.tbNameOfOutputFile.TabIndex = 8;
            this.tbNameOfOutputFile.Text = "MySudokuPuzzle";
            // 
            // btnGenerate
            // 
            this.btnGenerate.Image = global::SudokuGenerator.Properties.Resources.database_gear;
            this.btnGenerate.Location = new System.Drawing.Point(572, 170);
            this.btnGenerate.Name = "btnGenerate";
            this.btnGenerate.Size = new System.Drawing.Size(110, 42);
            this.btnGenerate.TabIndex = 9;
            this.btnGenerate.Text = "Generate";
            this.btnGenerate.TextImageRelation = System.Windows.Forms.TextImageRelation.ImageBeforeText;
            this.btnGenerate.UseVisualStyleBackColor = true;
            this.btnGenerate.Click += new System.EventHandler(this.btnGenerate_Click);
            // 
            // button1
            // 
            this.button1.FlatAppearance.BorderSize = 0;
            this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.button1.Image = global::SudokuGenerator.Properties.Resources.Blue_Folder;
            this.button1.Location = new System.Drawing.Point(640, 21);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(42, 29);
            this.button1.TabIndex = 6;
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // frmSudokuGenerator
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.ClientSize = new System.Drawing.Size(700, 231);
            this.Controls.Add(this.btnGenerate);
            this.Controls.Add(this.tbNameOfOutputFile);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.lblOutputFileTo);
            this.Controls.Add(this.tbOutputFileLocation);
            this.Controls.Add(this.rbIntemediate);
            this.Controls.Add(this.rbEasy);
            this.Controls.Add(this.lblNumOfPuzzles);
            this.Controls.Add(this.tbNumOfPuzzles);
            this.Font = new System.Drawing.Font("Corbel", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "frmSudokuGenerator";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "SudokuGenerator";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbNumOfPuzzles;
        private System.Windows.Forms.Label lblNumOfPuzzles;
        private System.Windows.Forms.RadioButton rbEasy;
        private System.Windows.Forms.RadioButton rbIntemediate;
        private System.Windows.Forms.TextBox tbOutputFileLocation;
        private System.Windows.Forms.Label lblOutputFileTo;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.FolderBrowserDialog fbdOutputFile;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbNameOfOutputFile;
        private System.Windows.Forms.Button btnGenerate;
    }
}

