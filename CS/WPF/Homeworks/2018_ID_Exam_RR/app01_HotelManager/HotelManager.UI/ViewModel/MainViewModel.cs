using System.Collections.ObjectModel;
using HotelManager.Model;
using HotelManager.UI.Data;

namespace HotelManager.UI.ViewModel
{

    public class MainViewModel : ViewModelBase
    {
        private IRoomDataService _roomDataService;
        private Room _selectedRoom;


        public MainViewModel(IRoomDataService roomDataService)
        {
            Rooms = new ObservableCollection<Room>();
            _roomDataService = roomDataService;
        }

        public void Load()
        {
            var rooms = _roomDataService.GetAll();
            Rooms.Clear();
            foreach (var room in rooms)
            {
                Rooms.Add(room);
            }
        }

        public ObservableCollection<Room> Rooms { get; set; }

        public Room SelectedRoom
        {
            get { return _selectedRoom; }
            set
            {
                _selectedRoom = value;
                OnPropertyChanged();
            }
        }

    }
}
