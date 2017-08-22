using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ShaneLibWrapper;
using System.Diagnostics;

namespace SudokuGenerator
{
    public partial class frmSudokuGenerator : Form
    {
        private string OutputDirectory;
        private int NumPuzzles;

        public frmSudokuGenerator()
        {
            InitializeComponent();
            SetupValues();
        }

        private void SetupValues()
        {
            OutputDirectory = tbOutputFileLocation.Text = Environment.CurrentDirectory;
            tbNameOfOutputFile.Text = GetStartupDateString();
        }

        private string GetStartupDateString()
        {
            return String.Format("Sudoku_{0}-{1}-{2}",
                DateTime.Now.Day,
                DateTime.Now.Month,
                DateTime.Now.Year);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OutputDirectory = String.Empty;
            if (fbdOutputFile.ShowDialog() == DialogResult.OK)
            {
                OutputDirectory = fbdOutputFile.SelectedPath;                 
            }
            tbOutputFileLocation.Text = OutputDirectory;
        }

        private void btnGenerate_Click(object sender, EventArgs e)
        {
            if (isInputValid())
            {
                TryGeneratePuzzles();                
            }
        }

        private bool isInputValid()
        {
            return isDirectoryValid()
                && isFileNameValid()
                && isNumPuzzlesValid();
        }

        private bool isDirectoryValid()
        {
            bool Exists = true;
            if (!Directory.Exists(OutputDirectory))
            {
                Exists = false;
                ShowError(String.Format("Directory '{0}' does not exist", OutputDirectory));
            }
            return Exists;
        }

        private bool isFileNameValid()
        {
            bool FileNotEmpty = true;
            if (String.IsNullOrEmpty(tbNameOfOutputFile.Text))
            {
                FileNotEmpty = false;
                ShowError("Please enter a name for the ouput file");
            }
            bool FileNotExist = true;
            if (File.Exists(GetOutputFilePath()))
            {
                FileNotExist = false;
                ShowError(String.Format("'{0}' already exists", GetOutputFilePath()));
            }
            return FileNotEmpty && FileNotExist;
        }

        private string GetOutputFilePath()
        {
            return String.Format(@"{0}\{1}.pdf", OutputDirectory, tbNameOfOutputFile.Text);
        }

        private bool isNumPuzzlesValid()
        {
            if(!int.TryParse(tbNumOfPuzzles.Text, out NumPuzzles))
            {
                ShowError(String.Format("{0} is an invalid number", tbNumOfPuzzles.Text));
                return false;
            }
            else
            {
                return true;
            }            
        }

        private void TryGeneratePuzzles()
        {
            try
            {
                Cursor = Cursors.WaitCursor;
                GeneratePuzzles();                
            }
            catch (Exception ex)
            {
                Cursor = Cursors.Default;
                MessageBox.Show(ex.Message);
            }
        }

        private void GeneratePuzzles()
        {
            Puzzles p = new Puzzles();
            p.CreateThePuzzles(true, NumPuzzles, rbIntemediate.Checked);
            iTextSharpWrapper.GeneratePDF(p.PuzzlesListPrintableOrder, GetOutputFilePath());
            Cursor = Cursors.Default;
            Process.Start(GetOutputFilePath());
        }

        private void ShowError(string Message)
        {
            MessageBox.Show(Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }
}
