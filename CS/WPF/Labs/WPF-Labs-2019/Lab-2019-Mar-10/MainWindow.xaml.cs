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

        #region Selection Listeners

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

        #endregion

        #region Action Reults

        private string SayHello(string s)
        {
            return "Hello, " + s + " !  your name has " + s.CountDistinctLetters() + " distinct letters";
        }

        #endregion

        private void PrepareInput()
        {
            ClearInputAndResult();
            switch (SelectedOption)
            {
                case "rbHello":
                    lblInfo.Content = new TextBlock() { Text = "Enter your name" };
                    break;
                case "rbAverage":
                    lblInfo.Content = new TextBlock() { Text = "Enter some numbers (space separated)" };
                    break;
                case "rbCheckPalindrom":
                    lblInfo.Content = new TextBlock() { Text = "Enter any word to check if it is a palindrom" };
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
            bool isValid = true;

            if (string.IsNullOrWhiteSpace(txtInpt.Text))
            {
                lblResult.Text = "Enter something in input first";
                lblResultBorder.BorderBrush = System.Windows.Media.Brushes.Red;
                return false;
            }

            switch (SelectedOption)
            {
                case "rbHello":
                    break;
                case "rbAverage":
                    if (txtInpt.Text.Contains(","))
                    {
                        lblResult.Text = "Invalid numbers";
                        isValid = false;
                    }
                    char[] charsArray = txtInpt.Text.ToCharArray();
                    foreach (char c in charsArray)
                    {
                        if (!char.IsWhiteSpace(c) && !char.IsDigit(c))
                        {
                            lblResult.Text = "Invalid character: \"" + c + " \"";
                            isValid = false;
                            lblResultBorder.BorderBrush = System.Windows.Media.Brushes.Red;
                            return isValid;
                        }
                    }

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

        private void btnOk_Click(object sender, RoutedEventArgs e)
        {
            var userInput = txtInpt.Text;
            HandleUserInput(userInput);
        }

        #region RbHandlers
        private void HandleUserInput(string userInput)
        {
            if (!IsInputValid())
            {
                return;
            }

            switch (SelectedOption)
            {
                case "rbHello":
                    HandleRbHello(userInput);
                    break;
                case "rbAverage":
                    HandleRbAverage(userInput);
                    break;
                case "rbCheckPalindrom":
                    handleRbPalindrom(userInput);
                    break;
            }

            lblResultBorder.BorderBrush = System.Windows.Media.Brushes.Blue;
        }

        private void handleRbPalindrom(string userInput)
        {
            lblResult.Text = "\"" + txtInpt.Text + " \"" +
                             (userInput.IsPalindrom() ? " is a palindrom" : " is not a palindrom");
        }

        private void HandleRbAverage(string userInput)
        {
            List<int> listOfNumbers = userInput.SplitStringIntoNumbers();
            float m = Utils.Average(listOfNumbers);
            lblResult.Text = "The average is: " + m.ToString("##.00");
        }
        #endregion

        private void HandleRbHello(string userInput)
        {
            lblResult.Text = SayHello(userInput).ToString();
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
