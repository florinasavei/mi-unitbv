using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Word = Microsoft.Office.Interop.Word;

namespace FileMerger
{
    public partial class MainWindow
    {
        public static void Merge(List<string>filesToMerge, string outputFilename, bool insertPageBreaks, string documentTemplate = "")
        {

            if (filesToMerge.Capacity == 0)
            {
                System.Windows.MessageBox.Show("No Files to be merged!");

                return;
            }

            if (File.Exists(outputFilename))
            {
                FileInfo file = new FileInfo(outputFilename);
                MainWindow.Rename(file,"Combined_" + DateTime.Now.ToString("yyyyMMddHHmmss") + ".docx");
            }

            //object defaultTemplate = documentTemplate; //not sure what this does
            object missing = System.Type.Missing;
            object pageBreak = Word.WdBreakType.wdSectionBreakNextPage;
            object outputFile = outputFilename;

            // Create a new Word application
            Word._Application wordApplication = new Word.Application();

            try
            {
                // Create a new file based on our template
                Word.Document wordDocument = wordApplication.Documents.Add(
                                              ref missing
                                            , ref missing
                                            , ref missing
                                            , ref missing);

                // Make a Word selection object.
                Word.Selection selection = wordApplication.Selection;

                //Count the number of documents to insert;
                int documentCount = filesToMerge.Capacity;

                //A counter that signals that we shoudn't insert a page break at the end of document.
                int breakStop = 0;

                // Loop thru each of the Word documents
                foreach (string file in filesToMerge)
                {
                    breakStop++;
                    // Insert the files to our template
                    selection.InsertFile(
                                                file
                                            , ref missing
                                            , ref missing
                                            , ref missing
                                            , ref missing);

                    //Do we want page breaks added after each documents?
                    if (insertPageBreaks && breakStop != documentCount)
                    {
                        selection.InsertBreak(ref pageBreak);
                    }

                    selection.TypeText("some extra text");
                }

                // Save the document to it's output file.
                wordDocument.SaveAs(
                                ref outputFile
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing
                            , ref missing);

                // Clean up!
                wordDocument = null;
            }
            catch (Exception ex)
            {
                //I didn't include a default error handler so i'm just throwing the error
                throw ex;
            }
            finally
            {
                // Finally, Close our Word application
                wordApplication.Quit(ref missing, ref missing, ref missing);
            }
        }

        public static void Rename(FileInfo fileInfo, string newName)
        {
            fileInfo.MoveTo(fileInfo.Directory.FullName + "\\" + newName);
        }
    }
}
