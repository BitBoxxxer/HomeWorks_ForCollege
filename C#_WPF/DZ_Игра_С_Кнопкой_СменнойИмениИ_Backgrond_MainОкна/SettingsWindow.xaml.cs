using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace ButtonCatcher
{
    public partial class SettingsWindow : Window
    {
        private MainWindow mainWindow; // Ссылка на главное окно

        public SettingsWindow(MainWindow mainWindow)
        {
            InitializeComponent();
            this.mainWindow = mainWindow; // Сохраняем ссылку на главное окно
        }

        public void btnSave_Click(object sender, RoutedEventArgs e)
        {
            string playerName = txtPlayerName.Text;

            // Получаем выбранный цвет
            string selectedColor = (colorComboBox.SelectedItem as ComboBoxItem)?.Tag.ToString() ?? "LightGray";
            if (string.IsNullOrWhiteSpace(playerName)) { playerName = "Player_Name"; }

            // Меняем фон главного окна
            SetBackgroundColor(selectedColor);

            // Устанавливаем имя игрока
            SetPlayerName(playerName);

            // Отображаем сообщение
            MessageBox.Show($"Имя игрока: {playerName}\nЦвет фона: {selectedColor}");
            this.Close();
        }

        private void SetBackgroundColor(string colorname)
        {
            // Устанавливаем цвет фона в зависимости от выбранного имени цвета
            switch (colorname)
            {
                case "Red":
                    mainWindow.Background = Brushes.Red;
                    break;
                case "Green":
                    mainWindow.Background = Brushes.Green;
                    break;
                case "Blue":
                    mainWindow.Background = Brushes.Blue;
                    break;
                case "LightGray":
                    mainWindow.Background = Brushes.LightGray;
                    break;
                case "White":
                    mainWindow.Background = Brushes.White;
                    break;
                case "LightBlue":
                    mainWindow.Background = Brushes.LightBlue;
                    break;
                default:
                    mainWindow.Background = Brushes.LightGray; // Значение по умолчанию
                    break;
            }
        }

        private void SetPlayerName(string name)
        {
            MainWindow.playerName = name;
        }
    }
}