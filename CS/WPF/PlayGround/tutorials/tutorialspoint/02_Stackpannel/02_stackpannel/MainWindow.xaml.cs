﻿using System;
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

namespace _02_stackpannel
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            StackPanel stackPanel = new StackPanel();

            //this.Content = stackPanel;

            //// Create the Button 
            //Button button = new Button();
            //button.Content = "Click Me(code behinde!)";
            //button.HorizontalAlignment = HorizontalAlignment.Left;
            //button.Margin = new Thickness(150);
            //button.VerticalAlignment = VerticalAlignment.Top;
            //button.Width = 175;
            //stackPanel.Children.Add(button);

        }
    }
}
