using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using HotelManager.Model;
using HotelManager.UI.Data;
using HotelManager.UI.Event;
using Prism.Commands;
using Prism.Events;

namespace HotelManager.UI.ViewModel
{
    public class RoomDetailViewModel : ViewModelBase, IRoomDetailViewModel
    {
        private IRoomDataService _dataService;
        private Room _room;
        private IEventAggregator _eventAggregator;

        public RoomDetailViewModel(IRoomDataService dataService, IEventAggregator eventAggregator)
        {
            _dataService = dataService;
            _eventAggregator = eventAggregator;
            _eventAggregator.GetEvent<OpenRoomDetailViewEvent>()
                .Subscribe(OnOpenRoomDetailView);

            SaveCommand = new DelegateCommand(OnSaveExecute, OnSaveCanExecute);

        }

        private bool OnSaveCanExecute()
        {
            //todo: Check if friend is valid
            return true;
        }

        private async void OnSaveExecute()
        {
            await _dataService.SaveAsync(Room);

        }

        private async void OnOpenRoomDetailView(int RoomId)
        {
            await LoadAsync(RoomId);
        }

        public async Task LoadAsync(int roomId)
        {
            Room = await _dataService.GetByIdAsync(roomId);
        }

        public Room Room
        {
            get { return _room; }
            private set
            {
                _room = value;
                OnPropertyChanged();
            }
        }

        public ICommand SaveCommand { get; }


    }
}
