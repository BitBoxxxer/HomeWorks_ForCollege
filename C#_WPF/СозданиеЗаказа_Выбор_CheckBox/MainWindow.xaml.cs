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

namespace _17._03._25_WPF_Csh
{
    public partial class MainWindow : Window
    {
        
        public static List<string> list_txts = new List<string>();
        public static List<string> SelectedItems = new List<string>();
        public static List<string> Items_Names_List = new List<string>();

        public static int VodkaCount = 0, SvataiaVodkaCount = 0, SteikCount = 0;
        public static double VodkaPrice = 50.6, SvataiaVodkaPrice = 109.99, SteikPrice = 229.90;
        public static double VodkaPrice_Out = 0, SvataiaVodkaPrice_Out = 0, SteikPrice_Out = 0;

        public static double ALLPrice = 0;
        public static string NameProduct { get; set; }
        public static int NameCount { get; set; }
        public static double NamePrice { get; set; }

        public MainWindow()
        {
            InitializeComponent();
            CheckBox CheckBox_Items = new CheckBox();
            CheckBox_Items.Checked += CheckBox_Checked;
        }

        private void ButtonMain_Click(object sender, RoutedEventArgs e)
        {
            if (VodkaCount > 0 || SvataiaVodkaCount > 0 || SteikCount > 0)
            {
                Window1 w1 = new Window1();
                w1.Show();
                this.Close();
            }
            else
                MessageBox.Show("Ошибка, пустая корзина: наберите товара для оформления заказа.");
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            foreach (string i in SelectedItems)
            {
                list_txts.Remove(i.ToString());

                switch (i)
                {
                    case "Водка":
                        if (VodkaCount > 0)
                        {
                            VodkaCount--;
                            VodkaPrice_Out -= VodkaPrice;
                            ALLPrice -= VodkaPrice;
                        }
                        else
                        {
                            MessageBox.Show("Ошибка, наберите товара в корзину !");
                            return;
                        }
                        break;
                    case "Святая вода":
                        if (SvataiaVodkaCount > 0)
                        {
                            SvataiaVodkaCount--;
                            SvataiaVodkaPrice_Out -= SvataiaVodkaPrice;
                            ALLPrice -= SvataiaVodkaPrice;
                        }
                        else
                        {
                            MessageBox.Show("Ошибка, наберите товара в корзину !");
                            return;
                        }
                        break;
                    case "Стейк":
                        if (SteikCount > 0)
                        {
                            SteikCount--;
                            SteikPrice_Out -= SteikPrice;
                            ALLPrice -= SteikPrice;
                        }
                        else
                        {
                            MessageBox.Show("Ошибка, наберите товара в корзину !");
                            return;
                        }
                        break;
                }
                var existingItem = ListBox.Items.Cast<(string, int, string)>()
                    .FirstOrDefault(item => item.Item1 == i);

                if (VodkaCount == 0)
                    VodkaPrice_Out = 0;
                if (SvataiaVodkaCount == 0)
                    SvataiaVodkaPrice_Out = 0;
                if (SteikCount == 0)
                    SteikPrice_Out = 0;

                if (existingItem.Item1 != null)
                    ListBox.Items.Remove(existingItem);
                ListBox.Items.Add((i, (i == "Водка" ? VodkaCount : i == "Святая вода" ? SvataiaVodkaCount : SteikCount), "$ " + (i == "Водка" ? VodkaPrice_Out : i == "Святая вода" ? SvataiaVodkaPrice_Out : SteikPrice_Out) + " (" + (i == "Водка" ? VodkaCount : i == "Святая вода" ? SvataiaVodkaCount : SteikCount) + " штук) "));
            }
            if (VodkaCount == 0 && SvataiaVodkaCount == 0 && SteikCount == 0)
            {
                ALLPrice = 0;
            }
            TextBlock_Price.Text = "Итоговая Цена: " + ALLPrice;
        }


        private void ButtomAddItems_Click(object sender, RoutedEventArgs e)
        {
            foreach (string i in SelectedItems)
            {
                list_txts.Add(i.ToString());
                switch (i)
                {
                    case "Водка":
                        VodkaCount++;
                        VodkaPrice_Out += VodkaPrice;
                        ALLPrice += VodkaPrice;
                        break;
                    case "Святая вода":
                        SvataiaVodkaCount++;
                        SvataiaVodkaPrice_Out += SvataiaVodkaPrice;
                        ALLPrice += SvataiaVodkaPrice;
                        break;
                    case "Стейк":
                        SteikCount++;
                        SteikPrice_Out += SteikPrice;
                        ALLPrice += SteikPrice;
                        break;
                }
                var existingItem = ListBox.Items.Cast<(string, int, string)>()
                    .FirstOrDefault(item => item.Item1 == i);
                if (VodkaCount == 0)
                    VodkaPrice_Out = 0;
                if (SvataiaVodkaCount == 0)
                    SvataiaVodkaPrice_Out = 0;
                if (SteikCount == 0)
                    SteikPrice_Out = 0;

                if (existingItem.Item1 != null)
                    ListBox.Items.Remove(existingItem);
                ListBox.Items.Add((i, (i == "Водка" ? VodkaCount : i == "Святая вода" ? SvataiaVodkaCount : SteikCount), "$ " + (i == "Водка" ? VodkaPrice_Out : i == "Святая вода" ? SvataiaVodkaPrice_Out : SteikPrice_Out) + " (" + (i == "Водка" ? VodkaCount : i == "Святая вода" ? SvataiaVodkaCount : SteikCount) + " штук) "));
            }
            if (VodkaCount == 0 && SvataiaVodkaCount == 0 && SteikCount == 0)
                ALLPrice = 0;
            TextBlock_Price.Text = "Итоговая Цена: " + ALLPrice;
        }

        private void CheckBox_Checked(object sender, RoutedEventArgs e)
        {
            SelectedItems.Add((e.OriginalSource as CheckBox).Content.ToString());
        }
        private void CheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            SelectedItems.Remove((e.OriginalSource as CheckBox).Content.ToString());
        }

        // Отбросы:
        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}
