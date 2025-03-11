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

namespace WpfApp1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void ButtonBIG_Click(object sender, RoutedEventArgs e)
        {
            /*int q = Convert.ToInt32(TBOXs1.Text);
            int q2 = Convert.ToInt32(TBOXs2.Text);

            ButtonBIG.Content = q + q2;
            MessageBoxResult w = MessageBox.Show("TEXT.EXE", "AAAAAAA", MessageBoxButton.OKCancel);
*/
            string q = TBOXs1.Text; string q2 = TBOXs2.Text; string q3 = TBOXs3.Text;

            for(int i =0; i < 3; i++)
            {
                switch(i)
                {
                    case 0:
                        MessageBoxResult w = MessageBox.Show(q);
                        break;
                    case 1:
                        MessageBoxResult w1 = MessageBox.Show(q2);
                        break;
                    case 2:
                        MessageBoxResult w2 = MessageBox.Show(q3);
                        break;
                }
            }
            MessageBoxResult counts = MessageBox.Show("Колличество боксов: 3. Колличество символов" +
                ": " + (q.Length + q2.Length + q3.Length));
        }
        private void ButtonBot_Click(object sender, RoutedEventArgs e)
        {
            int user_number = Convert.ToInt32(TBOXBIG.Text);
            int bot_number = 0;

            MessageBoxResult w = MessageBox.Show("Да - чтобы продолжить. Нет - чтобы дать хук боту и победить его.", "Выбор судьбы.", MessageBoxButton.YesNo);

            if (w == MessageBoxResult.Yes)
            {
                while (bot_number != user_number)
                {
                    bot_number++;
                    if (bot_number == user_number)
                        break;
                }
                MessageBoxResult res = MessageBox.Show("Всего попыток боту понадобилось: " + bot_number);
            }
            if (w == MessageBoxResult.No)
            {
                MessageBoxResult res = MessageBox.Show("Бот умер. Это ваша вина.");
            }

        }
    }
}
