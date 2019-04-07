using System;
using System.Windows;
using Microsoft.WindowsAPICodePack.Dialogs;

namespace WPF_FileExplorer
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

        private void BtnOpen_Click(object sender, RoutedEventArgs e)
        {
            using (CommonOpenFileDialog cfd = new CommonOpenFileDialog(){IsFolderPicker = true})
            {
                if (cfd.ShowDialog() == CommonFileDialogResult.Ok)
                {
                    fileBrowser.Source = new Uri(cfd.FileName);
                    txtPath.Text = cfd.FileName;
                }
            }
        }

        private void BtnBack_Click(object sender, RoutedEventArgs e)
        {
            if (fileBrowser.CanGoBack)
            {
                fileBrowser.GoBack();
            }
        }

        private void BtnForward_Click(object sender, RoutedEventArgs e)
        {
            if (fileBrowser.CanGoForward)
            {
                fileBrowser.GoForward();
            }
        }
    }
}
