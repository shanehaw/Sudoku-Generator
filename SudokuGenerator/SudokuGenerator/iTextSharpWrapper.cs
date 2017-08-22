using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using iTextSharp.text;
using iTextSharp.text.pdf;
using System.IO;

namespace SudokuGenerator
{
    public class iTextSharpWrapper
    {
        public static void GeneratePDF(List<int[,]> puzzles, string URL)
        {
            Document doc = new Document();
            
            try
            {
                PdfWriter writer = PdfWriter.GetInstance(doc, new FileStream(URL, FileMode.Create));
                doc.Open();

                PdfPTable main = new PdfPTable(2);
                main.SetWidths(new int[] { 1, 1 });
                main.SpacingAfter = 0f;
                main.TotalWidth = 500;
                main.LockedWidth = true;

                for (int p = 0; p < puzzles.Count; p++)
                {                                         
                    PdfPTable tbl = new PdfPTable(9);
                    tbl.SetWidths(new int[] { 1, 1, 1, 1, 1, 1, 1, 1, 1 });
                    tbl.SpacingAfter = 0f;
                    tbl.TotalWidth = 200;
                    tbl.LockedWidth = true;

                    for (int i = 0; i < 9; i++)
                    {
                        for (int j = 0; j < 9; j++)
                        {
                            PdfPCell c = new PdfPCell(new Phrase(puzzles[p][i, j] != 0 ? puzzles[p][i, j].ToString() : " "));
                            c.HorizontalAlignment = PdfPCell.ALIGN_CENTER;
                            c.Border = PdfPCell.NO_BORDER;
                            c.BorderWidthBottom = 0.5f;
                            c.PaddingBottom = 5f;
                            c.PaddingTop = 5f;

                            if (i == 0)
                                c.BorderWidthTop = 2;

                            if (j == 0)
                                c.BorderWidthLeft = 2;

                            if (j == 8)
                                c.BorderWidthRight = 2;

                            if (i == 8)
                                c.BorderWidthBottom = 2;

                            if (i % 3 == 0)
                                c.BorderWidthTop = 2;

                            if (j % 3 == 2)
                                c.BorderWidthRight = 2;
                            else
                                c.BorderWidthRight = 0.5f;

                            tbl.AddCell(c);
                        }
                    }

                    PdfPCell newCell = new PdfPCell(tbl);
                    newCell.Border = PdfPCell.NO_BORDER;
                    newCell.PaddingBottom = 15f;
                    main.AddCell(newCell);
                }

                PdfPCell footer2 = new PdfPCell(new Phrase("Shane Haw  © 2012"));
                footer2.Colspan = 2;                
                footer2.PaddingRight = 28f;
                footer2.HorizontalAlignment = PdfPCell.ALIGN_RIGHT;
                footer2.Border = PdfPCell.NO_BORDER;
                footer2.PaddingTop = 10f;
                main.AddCell(footer2);

                doc.Add(main);

                doc.AddAuthor("Shane Haw");
                doc.AddCreationDate();                
            }
            catch (DocumentException de)
            {
                Console.Out.WriteLine(de.Message);
                throw;
            }

            doc.Close();
        }
    }
}
