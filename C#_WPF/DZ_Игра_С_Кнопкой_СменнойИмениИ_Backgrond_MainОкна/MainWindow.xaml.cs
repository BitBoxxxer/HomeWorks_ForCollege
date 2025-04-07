using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;
using System.Windows.Threading;

namespace ButtonCatcher
{
    public partial class MainWindow : Window
    {
        private int score = 0;
        private DispatcherTimer timer;
        private Random random = new Random();
        public static string playerName = "Player_Name";

        //MainWindow.SetPlayerName(playerName);
        //MainWindow.SetBackgroundColor(selectedColor);
        public MainWindow()
        {
            InitializeComponent();
            
            
        }

        private void btnStart_Click(object sender, RoutedEventArgs e)
        {
            score = 0;
            ScoreText.Text = $"Игрок: {playerName}\nСчет: {score}"/*"\n" "Счет: " + score*/;
            StartGame();
        }

        private void StartGame()
        {
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e)
        {
            CreateButton();
        }

        private void CreateButton()
        {
            Button button = new Button();
            button.Content = "Тапаем";
            button.Click += Button_Click;
            button.Width = 100;
            button.Height = 50;

            double left = random.Next(0, (int)(GameGrid.ActualWidth - button.Width));
            double top = random.Next(0, (int)(GameGrid.ActualHeight - button.Height));
            Canvas.SetLeft(button, left);
            Canvas.SetTop(button, top);

            GameGrid.Children.Add(button);

            var fadeIn = new DoubleAnimation(0, 1, TimeSpan.FromSeconds(0.5));
            button.BeginAnimation(Button.OpacityProperty, fadeIn);

            var fadeOut = new DoubleAnimation(1, 0, TimeSpan.FromSeconds(0.5));
            fadeOut.Completed += (s, args) => GameGrid.Children.Remove(button);
            fadeOut.BeginTime = TimeSpan.FromSeconds(2);
            button.BeginAnimation(Button.OpacityProperty, fadeOut);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            score++;
            ScoreText.Text = $"Игрок: {playerName}\nСчет: {score}";
            Button button = sender as Button;
            GameGrid.Children.Remove(button);
        }

        private void btnSettings_Click(object sender, RoutedEventArgs e)
        {
            SettingsWindow settingsWindow = new SettingsWindow(this); // Передаем ссылку на главное окно
            settingsWindow.ShowDialog();
        }
    }
}
