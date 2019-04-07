using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;
namespace SearchingFileInWPF
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

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            this.cmbDrive.ItemsSource = DriveInfo.GetDrives().Where(dr => dr.IsReady == true).ToList();
            this.cmbDrive.DisplayMemberPath = "Name";
            this.cmbDrive.SelectedValuePath = "Name";
        }

        private void btnSearch_Click(object sender, RoutedEventArgs e)
        {
            //the list of myfolder that contains folder information
            List<MyFolder> FolderList = new List<MyFolder>();
            //create the object of directoryinfo
            DirectoryInfo DF = new DirectoryInfo(this.cmbDrive.SelectedValue.ToString());
           
            if (!string.IsNullOrEmpty(txtSearch.Text.Trim()))
            {
                // search the file and available in the directory based the criteria
                foreach (FileInfo FI in DF.GetFiles(this.txtSearch.Text.Trim()))
                {
                    this.DGVFileList.Items.Add(new MyFile() { Name = FI.Name, FullName = FI.FullName, Size = FI.Length, Type = FI.Extension, CreateDate = FI.CreationTime });
                }
            }
            else
            {
                foreach (FileInfo FI in DF.GetFiles())
                {
                    this.DGVFileList.Items.Add(new MyFile() { Name = FI.Name, FullName = FI.FullName, Size = FI.Length, Type = FI.Extension, CreateDate = FI.CreationTime });
                }
            }
            //retrives the directory(folder) information from your drive
            foreach (DirectoryInfo DIR in DF.GetDirectories())
            {
                //check whether the folder is accessable or not
                if (!DIR.Attributes.ToString().Contains("Hidden"))
                {
                    // search the file and available in the directory based the criteria
                    if (!string.IsNullOrEmpty(txtSearch.Text.Trim()))
                    {
                        foreach (FileInfo FI in DIR.GetFiles(this.txtSearch.Text.Trim()))
                        {
                            this.DGVFileList.Items.Add(new MyFile() { Name = FI.Name, FullName = FI.FullName, Size = FI.Length, Type = FI.Extension, CreateDate = FI.CreationTime });
                        }
                    }
                    else
                    {
                        // search the file and available in the directory 
                        foreach (FileInfo FI in DIR.GetFiles())
                        {
                            this.DGVFileList.Items.Add(new MyFile() { Name = FI.Name, FullName = FI.FullName, Size = FI.Length, Type = FI.Extension, CreateDate = FI.CreationTime });
                        }
                    }
                    //adds the folder into the list and set the searched property to fals
                    FolderList.Add(new MyFolder() { Name = DIR.Name, FullName = DIR.FullName, Searched = false });
                }
            }
            while (FolderList.Where(fl => fl.Searched == false).Count() > 0)
            {
                //retrives the folders whome files are not searched
                foreach (MyFolder MF in FolderList.Where(fl => fl.Searched == false).ToList())
                {
                    DirectoryInfo DIR = new DirectoryInfo(MF.FullName);
                    MF.Searched = true;
                    if (!DIR.Attributes.ToString().Contains("Hidden"))
                    {
                        if (!string.IsNullOrEmpty(txtSearch.Text.Trim()))
                        {
                            foreach (FileInfo FI in DIR.GetFiles(this.txtSearch.Text.Trim()))
                            {
                                this.DGVFileList.Items.Add(new MyFile() { Name = FI.Name, FullName = FI.FullName, Size = FI.Length, Type = FI.Extension, CreateDate = FI.CreationTime });
                            }
                        }
                        else
                        {
                            foreach (FileInfo FI in DIR.GetFiles())
                            {
                                this.DGVFileList.Items.Add(new MyFile() { Name = FI.Name, FullName = FI.FullName, Size = FI.Length, Type = FI.Extension, CreateDate = FI.CreationTime });
                            }
                        }
                        foreach (DirectoryInfo DR in DIR.GetDirectories())
                        {
                            FolderList.Add(new MyFolder() { Name = DR.Name, FullName = DR.FullName, Searched = false });
                        }
                    }
                }
            }
        }
    }
}
