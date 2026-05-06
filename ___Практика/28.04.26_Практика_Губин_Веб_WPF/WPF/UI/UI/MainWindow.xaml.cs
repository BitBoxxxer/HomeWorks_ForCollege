using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System;
using System.Net.Http;
using System.Net.Http.Json;
using System.Threading.Tasks;
using System.Windows.Threading;

namespace UI
{
    public partial class MainWindow : Window
    {
        private HttpClient _http = new HttpClient() { BaseAddress = new Uri("http://localhost:5000") };
        private DispatcherTimer _timer;
        private Random _rand = new Random();
        private bool _isRunning = false;

        public MainWindow()
        {
            InitializeComponent();
            _timer = new DispatcherTimer { Interval = TimeSpan.FromSeconds(5) };
            _timer.Tick += Timer_Tick;
        }

        private async void Timer_Tick(object sender, EventArgs e)
        {
            double temp = Math.Round(_rand.NextDouble() * 30 + 10, 1); // 10..40
            var data = new { Temperature = temp, Timestamp = DateTime.Now };
            try
            {
                var response = await _http.PostAsJsonAsync("/api/temperature", data);
                response.EnsureSuccessStatusCode();
                LastTempText.Text = $"Последняя: {temp} °C (отправлено)";
                StatusText.Text = $"✅ {DateTime.Now:HH:mm:ss} - OK";
            }
            catch (Exception ex)
            {
                StatusText.Text = $"ERR: {ex.Message}";
            }
        }

        private void OnStartStopClick(object sender, RoutedEventArgs e)
        {
            if (_isRunning)
            {
                _timer.Stop();
                StartStopButton.Content = "Старт";
                StatusText.Text = "Остановлен";
            }
            else
            {
                _timer.Start();
                StartStopButton.Content = "Стоп";
                StatusText.Text = "[Отправка каждые 5 сек]";
            }
            _isRunning = !_isRunning;
        }

        protected override void OnClosed(EventArgs e)
        {
            _timer.Stop();
            _http.Dispose();
            base.OnClosed(e);
        }
    }
}