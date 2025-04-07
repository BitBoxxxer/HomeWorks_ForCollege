using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
using System.Windows.Shapes;

namespace _26._03._25WPF
{
    public partial class Settings : Window
    {
        public static List<int> _listNumbersText = new List<int> 
        { 8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24 };

        public static List<string> _listThemes = new List<string>
        { "Серый", "Дефолт", "Белый", "Красный"};

        public static int normalNumberText = 12;

        public Settings()
        {
            InitializeComponent();
            CBNumbersText.SelectedItem = normalNumberText;
            CBNumbersText.ItemsSource = _listNumbersText;

            CBTheme.SelectedItem = "Дефолт";
            CBTheme.ItemsSource = _listThemes;

            FontSize = Convert.ToInt32(CBNumbersText.Text);
        }

        private void MainButt_Click(object sender, RoutedEventArgs e)
        {
            MainWindow MW = new MainWindow();
            MW.Show();
            this.Close();
        }


        private void CBTheme_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void CBNumbersText_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            FontSize = Convert.ToInt32(CBNumbersText.Text);
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
        }
    }
}
