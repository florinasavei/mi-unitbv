using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HotelManager.Model;
using HotelManager.UI.Data;
using HotelManager.UI.Event;
using Prism.Events;

namespace HotelManager.UI.ViewModel
{
    public class NavigationViewModel : ViewModelBase, INavigationViewModel
    {
        private IRoomLookupDataService _RoomLookupService;
        private IEventAggregator _eventAgregator;


        public NavigationViewModel(IRoomLookupDataService roomLookupDataService, IEventAggregator eventAggregator)
        {
            _RoomLookupService = roomLookupDataService;
            _eventAgregator = eventAggregator;
            Rooms = new ObservableCollection<LookupItem>();

        }

        public async Task LoadAsync()
        {
            var lookup = await _RoomLookupService.GetRoomLookupAsync();
            Rooms.Clear();
            foreach (var item in lookup)
            {
                Rooms.Add(item);
            }
        }

        public ObservableCollection<LookupItem> Rooms { get; }

        private LookupItem _selectedRoom;

        public LookupItem SelectedRoom
        {
            get { return _selectedRoom; }
            set
            {
                _selectedRoom = value;
                OnPropertyChanged();
                if (_selectedRoom != null)
                {
                    _eventAgregator.GetEvent<OpenRoomDetailViewEvent>()
                        .Publish(_selectedRoom.Id);
                }
            }
        }

    }

}
