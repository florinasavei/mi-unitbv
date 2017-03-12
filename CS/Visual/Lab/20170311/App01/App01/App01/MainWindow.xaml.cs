using System;
using System.Collections.Generic;
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

namespace App01
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

   private void btnClick(object sender,MouseButtonEventArgs e)
    {
        MessageBox.Show("HelloWorld!!!"); 
    }

   private void btn_Click(object sender, RoutedEventArgs e)
   {
       //MessageBox.Show("HelloWorld again!!!");
       btn.Show(((Button) sender).Content.ToString())
       ;
   }

   private void Button_Click(object sender, RoutedEventArgs e)
   {

   }


    }

   
}

