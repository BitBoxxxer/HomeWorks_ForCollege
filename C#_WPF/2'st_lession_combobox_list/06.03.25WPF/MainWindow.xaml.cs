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

namespace _06._03._25WPF
{
    public partial class MainWindow : Window
    {
        List<string> Array = new List<string>() {};

        static string job, ylica, city;
        public MainWindow()
        {
            InitializeComponent();
            ListBoxBIIIG.ItemsSource = Array;
            ComboBoxSmall.Items.Add("должность");
            ComboBoxSmall.Items.Add("город");
            ComboBoxSmall.Items.Add("улица");
        }
        private void ButtonCluentInf_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult res;
            res = MessageBox.Show("Список: " + Convert.ToString(ComboBoxSmall));

            switch (Convert.ToString(ComboBoxSmall.Items))
            {
                case "должность":
                    job = TextBoxBIG.Text;
                    res = MessageBox.Show("Изменена job: " + job);
                    break;
                case "город":
                    city = TextBoxBIG.Text;
                    res = MessageBox.Show("Изменена city: " + city);
                    break;
                case "улица":
                    ylica = TextBoxBIG.Text;
                    res = MessageBox.Show("Изменена ylica: " + ylica);
                    break;
            }
        }
        private void ButtonResult_Click(object sender, RoutedEventArgs e)
        {
            MessageBoxResult res;
            if (job != "" && city != "" && ylica != "")
                Array.Add($"Должность: {job}. Город: {city}. Улица: {city}.");
            else
                res = MessageBox.Show("Ошибка, какие то поля пустые.");
        }

        private void ButtonComboBox_Click(object sender, RoutedEventArgs e)
        {
            ComboBoxSmall.Items.Add(TextBoxBIG.Text);
            MessageBoxResult res = MessageBox.Show("Добавлена новая переменная в ComBox: " + TextBoxBIG.Text);
        }

        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {

        }


        private void ComboBoxSmall_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void ListBoxBIIIG_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

    }
}
