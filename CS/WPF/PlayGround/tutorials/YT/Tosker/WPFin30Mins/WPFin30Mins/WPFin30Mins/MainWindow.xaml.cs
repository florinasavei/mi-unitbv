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
using WPFin30Mins.Models;

namespace WPFin30Mins
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private string Name = "Hello World";

        public MainWindow()
        {
            InitializeComponent();
            MyModelObject button1DataContext = new MyModelObject() {Name = "I'm button 1"};
            MyModelObject button2DataContext = new MyModelObject() {Name = "I'm button 2"};

            button1.DataContext = button1DataContext;
            button2.DataContext = button2DataContext;

        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            mainGridPannel.Background = Brushes.BlueViolet;
        }
    }
}
