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

namespace Lab_2019_Mar_10
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

        private void RadioButton_Checked(object sender, RoutedEventArgs e)
        {

        }

        public delegate void DoAction();

        public DoAction _myAction { get; set; }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            _myAction();
        }

        private void OptionsMenu_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            RadioButton selectedRadio = (System.Windows.Controls.RadioButton)OptionsMenu.SelectedItems[0];
            HandleSelectionChanged(selectedRadio);
        }

        private void HandleSelectionChanged(RadioButton selectedRadio)
        {
            string selectedRadioName = selectedRadio.Name;
            switch (selectedRadioName)
            {
                case "rbHello":
                    PrepareInput(selectedRadioName);
                    _myAction = SayHello;
                    break;
                case "rbAverage":
                    PrepareInput(selectedRadioName);
                    _myAction = CalcualteAverage;
                    break;
                case "rbCheckPalindrom":
                    PrepareInput(selectedRadioName);
                    _myAction = CheckPalindrom;
                    break;
            }
        }
     
        private void SayHello()
        {
            lblInput.Text = "Enter your name";
            lblResult.Text = "Hello " + txtInpt.Text + " !";
        }

        private void CalcualteAverage()
        {
            throw new NotImplementedException();
        }

        private void CheckPalindrom()
        {
            throw new NotImplementedException();
        }


        private void PrepareInput(string selectedRadioName)
        {
            ClearInput();
            switch (selectedRadioName)
            {
                case "rbHello":
                    lblInput.Text = "Enter your name";
                    break;
                case "rbAverage":
                    lblInput.Text = "Enter some numbers (comma separated)";
                    break;
                case "rbCheckPalindrom":
                    lblInput.Text = "Enter any text";
                    break;
            }
        }

        private void ClearInput()
        {
           
        }

        private void RbHello_OnClick(object sender, RoutedEventArgs e)
        {
            RadioButton radioName = (System.Windows.Controls.RadioButton)sender;
            HandleSelectionChanged(radioName);
        }
    }
}
