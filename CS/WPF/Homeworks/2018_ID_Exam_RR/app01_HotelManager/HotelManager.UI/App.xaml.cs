using System.Windows;
using HotelManager.UI.Data;
using HotelManager.UI.ViewModel;

namespace HotelManager.UI
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        private void App_OnStartup(object sender, StartupEventArgs e)
        {
            var mainWindow = new MainWindow(
                new MainViewModel(new RoomDataService()));

            mainWindow.Show();
        }
    }
}
