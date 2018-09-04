using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace HotelManager.Model
{
    public class Reservation
    {
        [Required]
        public int Id { get; set; }

        public ReservationStatus Status { get; set; }

        public bool IsDeleted { get; set; }

        public List<Room> ReservedRooms { get; set; }

        public DateTime ReservedFrom { get; set; }

        public DateTime ReservedUntil { get; set; }

        public byte NumberOrPeople { get; set; }

        public int NumberOfDays { get; set; }

        public Decimal PricePerReservation { get; set; }

        [StringLength(500)]
        public string Comment { get; set; }

    }

    public enum ReservationStatus
    {
        None,
        Booked,
        Canceled
    }
}