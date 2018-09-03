using System;

namespace HotelManager.Model
{
    public class Reservation
    {
        public int ReservationId { get; set; }
        public DateTime ReservedFrom { get; set; }
        public DateTime ReservedUntil { get; set; }
    }
}