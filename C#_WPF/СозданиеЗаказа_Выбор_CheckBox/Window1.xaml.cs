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
using System.Windows.Shapes;

// ЭТО ДОП ОКНО !!!

namespace _17._03._25_WPF_Csh
{
    public partial class Window1 : Window
    {
        MainWindow MW = new MainWindow();
        public Window1()
        {
            InitializeComponent();
            List_End.ItemsSource = MainWindow.list_txts;
            TextB_End.Text = "Итоговая Цена: " + MainWindow.ALLPrice;
        }

        private void List_End_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            foreach (string i in MainWindow.list_txts)
            {
                List_End.Items.Add((i));
            }
        }

        private void Button_Price_Click(object sender, RoutedEventArgs e)
        {
            
        }
    }
}
