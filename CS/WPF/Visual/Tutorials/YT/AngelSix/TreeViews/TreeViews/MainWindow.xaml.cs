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
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Path = System.IO.Path;

namespace TreeViews
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        #region Constructor
        /// <summary>
        /// Default constructor
        /// </summary>
        public MainWindow()
        {
            InitializeComponent();
        }
        #endregion

        #region  On Loaded
        /// <summary>
        /// When the application first opens
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void MainWindow_OnLoaded(object sender, RoutedEventArgs e)
        {
            //Get every logical drive on the machine
            foreach (var drive in Directory.GetLogicalDrives())
            {
                var item = new TreeViewItem()
                {
                    //set the header
                    Header = drive,

                    //add the full path
                    Tag = drive
                };



                //add a dummy item
                item.Items.Add(null);

                //Listen out for item being expanded
                item.Expanded += Folder_Expanded;

                //add to main view;
                FolderView.Items.Add(item);

            }
        }

        #endregion

        private void Folder_Expanded(object sender, RoutedEventArgs e)
        {
            var item = (TreeViewItem)sender;

            //if the item only cintains the dummy data
            if (item.Items.Count != 1 && item.Items[0] != null)
                return;

            //clear dummy data
            item.Items.Clear();

            //get full path
            var fullpath = (string)item.Tag;

            //create a blank list of directories
            var directories = new List<string>();

            //Try get directories from the folder
            //ignoring any issues doing so
            try
            {
                var dir = Directory.GetDirectories(fullpath);

                if (dir.Length > 0)
                {
                    directories.AddRange(dir);
                }
            }
            catch
            {

            }

            //for each directory
            directories.ForEach(
                directoryPath =>
                {
                    //create directory item
                    var subItem = new TreeViewItem()
                    {
                        //set header as folder name
                        Header = GetFileFolderName(directoryPath),
                        //Add tag as full path
                        Tag = directoryPath

                    };

                    //Add dummy item so we can expand folder
                    subItem.Items.Add(null);

                    //Hnadle expanding
                    subItem.Expanded += Folder_Expanded;

                    //Add this item to the parent
                    item.Items.Add(subItem);

                });


        }

        /// <summary>
        /// Finds the file or folder name from a full path
        /// </summary>
        /// <param name="path"></param>
        /// <returns></returns>
        public static string GetFileFolderName(string path)
        {
            if (string.IsNullOrEmpty(path))
            {
                return string.Empty;
            }

            var normalizedPath = path.Replace('/', '\\');

            //find the last backslash in the path
            var lastIndex = normalizedPath.LastIndexOf('\\');

            //if we don't find a backslash, return the path inself
            if (lastIndex <= 0)
            {
                return path;
            }

            //return the name after the last slash
            return path.Substring(lastIndex + 1);


        }

    }
}
