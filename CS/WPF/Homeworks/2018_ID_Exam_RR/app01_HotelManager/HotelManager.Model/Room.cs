using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace HotelManager.Model
{
    public class Room
    {
        [Required]
        public int Id { get; set; }

        [Required]
        public int Number { get; set; }

        public RoomCategory Category { get; set; }

        public int Floor { get; set; }

        public int SingleBeds { get; set; }

        public int DoubleBeds { get; set; }

        public int NumberOfBedrooms { get; set; }

        public int NumberOfBaths { get; set; }

        public List<Amenity> Amenities { get; set; }

        public string Description { get; set; }

        public List<string> Pictures { get; set; }

        public List<RoomBasePrice> RoomBasePrices { get; set; }

        public List<Reservation> Reservations { get; set; }

    }

    public enum RoomCategory
    {
        Economy,
        Standard,
        Luxury,
        Business
    }
}
