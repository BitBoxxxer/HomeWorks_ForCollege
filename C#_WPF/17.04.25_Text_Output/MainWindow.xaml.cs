using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Threading;

namespace StoryGenerator
{
    public partial class MainWindow : Window
    {
        private Random random = new Random();
        private List<string> genres = new List<string> { "Грифены", "Аниме", "Яой" };
        private List<string> characters = new List<string> { "Винди", "Куплинов", "Аля Бридж", "Дед инсайд" };
        private DispatcherTimer typingTimer;
        private string storyToDisplay;
        private int currentCharIndex = 0;

        public MainWindow()
        {
            InitializeComponent();
            genreComboBox.ItemsSource = genres;
            charactersListBox.ItemsSource = characters;

            typingTimer = new DispatcherTimer();
            typingTimer.Interval = TimeSpan.FromMilliseconds(100);
            typingTimer.Tick += TypingTimer_Tick;
        }

        private void keywordsTextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            placeholderTextBlock.Visibility = string.IsNullOrWhiteSpace(keywordsTextBox.Text) ? Visibility.Visible : Visibility.Collapsed;
        }

        private void GenerateStory_Click(object sender, RoutedEventArgs e)
        {
            string genre = genreComboBox.SelectedItem?.ToString() ?? "Фэнтези";
            var selectedCharacters = charactersListBox.SelectedItems.Cast<string>().ToList();
            string keywords = keywordsTextBox.Text;

            string story = GenerateStory(genre, selectedCharacters, keywords);
            DisplayStoryWithTypingAnimation(story);
        }

        private string GenerateStory(string genre, List<string> characters, string keywords)
        {
            string character = (characters.Count > 0) ? characters[random.Next(0, characters.Count)] : "Персонаж";
            string theme = keywords.Length > 0 ? $", о {keywords}" : "";

            return $"{genre} история: {character} отправился в приключение{theme}. Конец.";
        }

        private void DisplayStoryWithTypingAnimation(string story)
        {
            storyToDisplay = story;
            currentCharIndex = 0;
            storyTextBlock.Text = string.Empty;
            typingTimer.Start();
        }

        private void TypingTimer_Tick(object sender, EventArgs e)
        {
            if (currentCharIndex < storyToDisplay.Length)
            {
                storyTextBlock.Text += storyToDisplay[currentCharIndex];
                currentCharIndex++;
            }
            else
            {
                typingTimer.Stop();
            }
        }
    }
}