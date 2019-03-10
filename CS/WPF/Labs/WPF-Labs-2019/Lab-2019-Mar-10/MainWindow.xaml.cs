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

        public string SelectedOption { get; set; }

        public MainWindow()
        {
            InitializeComponent();
        }


        private void OptionsMenu_OnSelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            RadioButton selectedRadio = (System.Windows.Controls.RadioButton)OptionsMenu.SelectedItems[0];
            HandleSelectionChangedCommon(selectedRadio);
        }

        private void HandleSelectionChangedCommon(RadioButton selectedRadio)
        {
            ClearInputAndResult();

            SelectedOption = selectedRadio.Name;
            switch (SelectedOption)
            {
                case "rbHello":
                    SelectRadio();
                    PrepareInput();
                    break;
                case "rbAverage":
                    SelectRadio();
                    PrepareInput();
                    break;
                case "rbCheckPalindrom":
                    SelectRadio();
                    PrepareInput();
                    break;
            }
        }

        private void SelectRadio()
        {
            rbHello.IsChecked = false;
            rbAverage.IsChecked = false;
            rbCheckPalindrom.IsChecked = false;

            switch (SelectedOption)
            {
                case "rbHello":
                    rbHello.IsChecked = true;
                    break;
                case "rbAverage":
                    rbAverage.IsChecked = true;
                    break;
                case "rbCheckPalindrom":
                    rbCheckPalindrom.IsChecked = true;
                    break;
            }
        }

        #region Action Reults

        private string SayHello(string s)
        {
            return "Hello, " + s + " !  your name has " + s.Length + " characters";
        }

        private float Average(List<int> numbers)
        { 
            return (float)numbers.Average();
        }

        private List<int> GetNumbersFromString(string s)
        {
            try
            {
                return new List<int>(Array.ConvertAll(s.Split(' '), int.Parse));
            }
            catch (Exception e)
            {
                lblResult.Text = "Invalid numbers";
                throw new Exception(e.Message);
            }
        }

        private bool IsPalindrom(string s)
        {
            string myString = s.ToLower();
            string reversedString = new string(myString.Reverse().ToArray());
            return string.CompareOrdinal(myString, reversedString) == 0;
        }

        #endregion

        private void PrepareInput()
        {
            ClearInputAndResult();
            switch (SelectedOption)
            {
                case "rbHello":
                    lblInput.Text = "Enter your name";
                    break;
                case "rbAverage":
                    lblInput.Text = "Enter some numbers (space separated)";
                    break;
                case "rbCheckPalindrom":
                    lblInput.Text = "Enter any text";
                    break;
            }
        }

        private void ClearInputAndResult()
        {
            txtInpt.Text = "";
            lblResult.Text = "";
            lblResultBorder.BorderBrush = System.Windows.Media.Brushes.Black;
        }

        private bool IsInputValid()
        {
            bool isValid = false;

            if (string.IsNullOrWhiteSpace(txtInpt.Text))
            {
                lblResult.Text = "Enter something in input first";
                lblResultBorder.BorderBrush = System.Windows.Media.Brushes.Red;
                return false;
            }

            switch (SelectedOption)
            {
                case "rbHello":
                    isValid = true;
                    break;
                case "rbAverage":
                    if (txtInpt.Text.Contains(","))
                    {
                        lblResult.Text = "Invalid numbers";
                        isValid = false;
                    }
                    if (!char.IsDigit(txtInpt.Text[0]))
                    {
                        lblResult.Text = "Invalid characters";
                        isValid =  false;
                    }
                    isValid = true;
                    break;
                case "rbCheckPalindrom":
                    isValid = true;
                    break;
            }

            if (!isValid)
            {
                lblResultBorder.BorderBrush = System.Windows.Media.Brushes.Red;
            }

            return isValid;
        }


        private void Button_Click(object sender, RoutedEventArgs e)
        {
            switch (SelectedOption)
            {
                case "rbHello":
                    if (!IsInputValid())
                    {
                        return;
                    }
                    lblResult.Text = SayHello(txtInpt.Text).ToString();
                    break;
                case "rbAverage":
                    if (!IsInputValid())
                    {
                        return;
                    }
                    List<int> listOfNumbers = GetNumbersFromString(txtInpt.Text);
                    lblResult.Text = "The average is: " + Average(listOfNumbers);
                    break;
                case "rbCheckPalindrom":
                    if (!IsInputValid())
                    {
                        return;
                    }
                    lblResult.Text = "\"" + txtInpt.Text + " \"" + (IsPalindrom(txtInpt.Text) ? " is a palindrom" : " is not a palindrom");
                    break;
            }

            lblResultBorder.BorderBrush = System.Windows.Media.Brushes.Blue;
        }

        private void RbHello_OnClick(object sender, RoutedEventArgs e)
        {
            RadioButton radioBtn = (System.Windows.Controls.RadioButton)sender;
            SelectedOption = radioBtn.Name;
            switch (SelectedOption)
            {
                case "rbHello":
                    OptionsMenu.SelectedIndex = 0;
                    break;
                case "rbAverage":
                    OptionsMenu.SelectedIndex = 1;
                    break;
                case "rbCheckPalindrom":
                    OptionsMenu.SelectedIndex = 2;
                    break;
            }
            HandleSelectionChangedCommon(radioBtn);
        }
    }
}
