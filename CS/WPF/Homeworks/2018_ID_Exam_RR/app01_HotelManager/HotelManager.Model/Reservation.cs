using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace HotelManager.Model
{
    public class Reservation
    {
        [Required]
        public int Id { get; set; }

        public List<Room> ReservedRooms { get; set; }

        public DateTime ReservedFrom { get; set; }

        public DateTime ReservedUntil { get; set; }

        public int NumberOfDays { get; set; }

        public Decimal PricePerReservation { get; set; }

    }
}