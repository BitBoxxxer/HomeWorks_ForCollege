using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System;
using System.Windows;
using static System.Console;

namespace MathFunc
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            Math _Math = new Math();
            _Math.MathOutPut();
            InitializeComponent();

        }

        private void Button_Start_Click1(object sender, RoutedEventArgs e)
        {
            //string text = textBox1.Text;
            if (textBox1.Text != "")
            {
                if (textBox1.Text == "Hello" || textBox1.Text == "Привет" || textBox1.Text == "Прив")
                {
                    MessageBox.Show("Hello uwu");
                }
                else
                {
                    MessageBox.Show(textBox1.Text);
                }

                //textBox1.Background = Brushes.LightGray;
            }
        }


        private void Button_Start_Click2(object sender, RoutedEventArgs e)
        {
            //string text = textBox2.Text;
            if (textBox2.Text != "")
            {
                MessageBox.Show(textBox2.Text);
                textBox1.Background = Brushes.LightBlue;
            }
        }

        int count;
        private void button_Click(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = new ListBoxItem();
            item.Content = "Item" + ++count;
            if (count < 4 + 1)
            {
                if (count % 2 == 0)
                {
                    item.Background = Brushes.LightGray;
                }
                else
                {
                    item.Background = Brushes.LightYellow;
                }
                listBox.Items.Add(item);
            }
        }

        private void button_Click_MathResult(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = new ListBoxItem();
            Math math = new Math();
            item.Content = math.Output_Result();
            ResultListBox.Items.Add(item);
        }
    }

    public class Math
    {
        private static string _MathSymbol;
        public static double _A; public static double _B; public static double _Result;

        public Math()
        {
            WriteLine("Выбирите что вы собираетесь делать с дальнейшими переменными: "); _MathSymbol = ReadLine();
            WriteLine("Введите переменную 'a': "); _A = Convert.ToDouble(ReadLine());
            WriteLine("Введите переменную 'b': "); _B = Convert.ToDouble(ReadLine());
        }

        public string Output_Result() => $"{_Result}";

        public void MathOutPut()
        {
            switch (_MathSymbol)
            {
                case "+":
                    {
                        double _Result = _A + _B;
                        break;
                    }

                case "-":
                    {
                        double _Result = _A - _B;
                        break;
                    }

                default: break;
            }
        }

    }
}
