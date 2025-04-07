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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace _26._03._25WPF
{
    public partial class MainWindow : Window
    {
        public static ObservableCollection<string> _listMain = new ObservableCollection<string>();

        public MainWindow()
        {
            InitializeComponent();
            List_WordsView.ItemsSource = _listMain;
            
        }

        private void SettsButt_Click(object sender, RoutedEventArgs e)
        {
            Settings STGS = new Settings();
            STGS.Show();
            this.Close();
        }

        private void ExitButt_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void ListButt_Click(object sender, RoutedEventArgs e)
        {
            _listMain.Add(TextBox.Text);
            this.InvalidateVisual();
        }

        private void ListView_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            int count = 1;
            foreach (var item in _listMain)
            {
                List_WordsView.Items.Add(count + item);
                count++;
            }
        }
    }
}
