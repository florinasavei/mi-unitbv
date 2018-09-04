using System.Threading.Tasks;

namespace HotelManager.UI.ViewModel
{

    public class MainViewModel : ViewModelBase
    {
        public MainViewModel(INavigationViewModel navigationViewModel, IRoomDetailViewModel roomDetailViewModel)
        {
            NavigationViewModel = navigationViewModel;
            RoomDetailViewModel = roomDetailViewModel;
        }

        public async Task LoadAsync()
        {
            await NavigationViewModel.LoadAsync();
        }

        public INavigationViewModel NavigationViewModel { get; }
        public IRoomDetailViewModel RoomDetailViewModel { get; }

    }
}
