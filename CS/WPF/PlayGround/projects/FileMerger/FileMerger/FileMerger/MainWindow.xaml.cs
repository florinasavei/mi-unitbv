using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace FileMerger
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void BtnSourcePathSelector_OnClick(object sender, RoutedEventArgs e)
        {
            var f = new FolderBrowserDialog
            {
                Description = @"Please the a folder containing the files you want to join:"
            };

            var result = f.ShowDialog();
            if (result == System.Windows.Forms.DialogResult.OK)
                rootSourcePath.Text = f.SelectedPath + @"\";
        }

       

        private void BtnJoinFiles(object sender, RoutedEventArgs e)
        {


            List<string> allWordDocuments = Directory.GetFiles( rootSourcePath.Text, "*.docx", SearchOption.AllDirectories)
                .Where(d => !MainWindow.isExcluded(d, rootSourcePath.Text))
                .ToList();
            string outputPath = rootSourcePath.Text + @"/_combined/Combined.docx";

            bool folderExists = Directory.Exists(rootSourcePath.Text + @"/_combined");
            if (!folderExists)
                Directory.CreateDirectory(rootSourcePath.Text + @"/_combined");

            allWordDocuments.Remove(outputPath);

            FileMerger.MainWindow.Merge(allWordDocuments, outputPath, true); 

        }

        static bool isExcluded( string target, string rootDirectory)
        {
            var dirName = System.IO.Path.GetDirectoryName(target);
            List<string> exludedDirList = new List<string>(new string[] { "_combined"});
            return exludedDirList.Any(d => dirName.Equals(rootDirectory + d));
        }

    }
}
