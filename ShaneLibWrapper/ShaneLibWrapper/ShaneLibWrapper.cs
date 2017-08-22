using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace ShaneLibWrapper
{
    public class Puzzle : IDisposable
    {
        //[DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        //private extern static IntPtr CreatePuzzleMinMissing(bool sorted, int min);

        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CreatePuzzle(bool sorted, bool intemediate);

        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Cleanup(IntPtr pis, int length);

        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void SolveThisPuzzle(IntPtr puzzle);

        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr PrintOrder(IntPtr puzzle);

        private IntPtr unmanagedPuzzle = IntPtr.Zero;

        private bool _Intemediate;
        public bool Intemediate
        {
            get { return _Intemediate; }
            set { _Intemediate = value; }
        }

        public int[,] PuzzleLogicalOrder
        {
            get 
            {
                if (unmanagedPuzzle != IntPtr.Zero)
                {
                    IntPtr[] x = new IntPtr[9];
                    Marshal.Copy(unmanagedPuzzle, x, 0, 9);

                    int[,] nums = new int[9, 9];
                    for (int i = 0; i < 9; i++)
                    {
                        int[] temp = new int[9];
                        Marshal.Copy(x[i], temp, 0, 9);
                        for (int j = 0; j < 9; j++)
                            nums[i, j] = temp[j];
                    }

                    return nums;
                }

                return new int[0,0];
            }
        }

        public int[,] PuzzlePrintOrder
        {
            get { return GetPrintableForm(); }
        }
        
        public void CreateThePuzzle()
        {
            unmanagedPuzzle = CreatePuzzle(false, _Intemediate);
            if (unmanagedPuzzle != IntPtr.Zero)
            {
                IntPtr[] x = new IntPtr[9];
                Marshal.Copy(unmanagedPuzzle, x, 0, 9);

                int[,] nums = new int[9, 9];
                for (int i = 0; i < 9; i++)
                {
                    int[] temp = new int[9];
                    Marshal.Copy(x[i], temp, 0, 9);
                    for (int j = 0; j < 9; j++)
                        nums[i, j] = temp[j];
                }
            }
        }

        //public void CreateThePuzzle(int min)
        //{
        //    unmanagedPuzzle = CreatePuzzleMinMissing(false, min);
        //    if (unmanagedPuzzle != IntPtr.Zero)
        //    {
        //        IntPtr[] x = new IntPtr[9];
        //        Marshal.Copy(unmanagedPuzzle, x, 0, 9);

        //        int[,] nums = new int[9, 9];
        //        for (int i = 0; i < 9; i++)
        //        {
        //            int[] temp = new int[9];
        //            Marshal.Copy(x[i], temp, 0, 9);
        //            for (int j = 0; j < 9; j++)
        //                nums[i, j] = temp[j];
        //        }
        //    }
        //}        

        public void SolveThePuzzle()
        {
            SolveThisPuzzle(unmanagedPuzzle);
            if (unmanagedPuzzle != IntPtr.Zero)
            {
                IntPtr[] x = new IntPtr[9];
                Marshal.Copy(unmanagedPuzzle, x, 0, 9);

                int[,] nums = new int[9, 9];
                for (int i = 0; i < 9; i++)
                {
                    int[] temp = new int[9];
                    Marshal.Copy(x[i], temp, 0, 9);
                    for (int j = 0; j < 9; j++)
                        nums[i, j] = temp[j];
                }
            }
        }

        public int[,] GetPrintableForm()
        {
            IntPtr printable = PrintOrder(unmanagedPuzzle);
            if (printable != IntPtr.Zero)
            {
                IntPtr[] x = new IntPtr[9];
                Marshal.Copy(printable, x, 0, 9);

                int[,] nums = new int[9, 9];
                for (int i = 0; i < 9; i++)
                {
                    int[] temp = new int[9];
                    Marshal.Copy(x[i], temp, 0, 9);
                    for (int j = 0; j < 9; j++)
                        nums[i, j] = temp[j];
                }
                return nums;
            }
            else
                return new int[0, 0];
        }

        private void CleanUpThePuzzle()
        {
            Cleanup(unmanagedPuzzle, 9);
        }

        public void Dispose()
        {
            CleanUpThePuzzle();
        }
    }

    public class Puzzles : IDisposable
    {
        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void Cleanup(IntPtr pis, int length);

        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void SolveThisPuzzle(IntPtr puzzle);

        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr PrintOrder(IntPtr puzzle);

        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CreatePuzzles(bool sorted, int num, bool intemediate);

        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static void CleanupPuzzles(int num, IntPtr puzzles);

        private IntPtr unmanagedPuzzleArr = IntPtr.Zero;
        public int NoOfPuzzles { get; set; }

        private bool _Intemediate;
        public bool Intemediate
        {
            get { return _Intemediate; }
            set { _Intemediate = value; }
        }

        private List<int[,]> _lPuzzles;
        public List<int[,]> PuzzlesListLogicalOrder
        {
            get
            {
                CreateThePuzzles(false, NoOfPuzzles, _Intemediate);                
                return _lPuzzles;
            }
        }

        public List<int[,]> PuzzlesListPrintableOrder
        {
            get
            {
                CreateThePuzzles(true, NoOfPuzzles, _Intemediate);
                return _lPuzzles;
            }
        }

        public void CreateThePuzzles(bool sorted, int num, bool intemediate)
        {
            this.NoOfPuzzles = num;
            unmanagedPuzzleArr = CreatePuzzles(sorted, num, intemediate);
            if (unmanagedPuzzleArr != null)
            {
                IntPtr[] x = new IntPtr[num];
                Marshal.Copy(unmanagedPuzzleArr, x, 0, num);

                _lPuzzles = new List<int[,]>();
                for (int i = 0; i < num; i++)
                {
                    IntPtr[] puzzle = new IntPtr[9];
                    Marshal.Copy(x[i], puzzle, 0, 9);                    

                    int[,] nums = new int[9,9];
                    for (int j = 0; j < 9; j++)
                    {
                        int[] temp = new int[9];
                        Marshal.Copy(puzzle[j], temp, 0, 9);
                        for (int k = 0; k < 9; k++)
                        {
                            nums[j, k] = temp[k];
                        }
                    }
                    _lPuzzles.Add(nums);
                }                
            }
        }

        public void Dispose()
        {
            CleanupPuzzles(NoOfPuzzles, unmanagedPuzzleArr);
        }
    }

    public class Library
    {
        [DllImport("ShaneLib.dll", CallingConvention = CallingConvention.Cdecl)]
        private extern static int Factorial(int num);

        public static int Fact(int num)
        {
            return Factorial(num);
        }
    }
}
