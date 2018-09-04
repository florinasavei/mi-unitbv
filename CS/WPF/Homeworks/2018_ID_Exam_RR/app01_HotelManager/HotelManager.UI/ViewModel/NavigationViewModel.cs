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
            Rooms = new ObservableCollection<NavigationItemViewModel>();
            _eventAgregator.GetEvent<AfterRoomSavedEvent>().Subscribe(AfterRoomSaved);

        }

        private void AfterRoomSaved(AfterRoomSavedEventArgs obj)
        {
            var lookupItem = Rooms.Single(l => l.Id == obj.Id);
            lookupItem.DisplayMember = obj.DisplayMember;
        }

        public async Task LoadAsync()
        {
            var lookup = await _RoomLookupService.GetRoomLookupAsync();
            Rooms.Clear();
            foreach (var item in lookup)
            {
                Rooms.Add(new NavigationItemViewModel(item.Id, item.DisplayMember));
            }
        }

        public ObservableCollection<NavigationItemViewModel> Rooms { get; }

        private NavigationItemViewModel _selectedRoom;

        public NavigationItemViewModel SelectedRoom
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
