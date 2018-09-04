using Prism.Events;

namespace HotelManager.UI.Event
{
    public class AfterRoomSavedEvent: PubSubEvent<AfterRoomSavedEventArgs>
    {
    }

    public class AfterRoomSavedEventArgs
    {
        public int Id { get; set; }
        public string DisplayMember { get; set; }
    }
}
