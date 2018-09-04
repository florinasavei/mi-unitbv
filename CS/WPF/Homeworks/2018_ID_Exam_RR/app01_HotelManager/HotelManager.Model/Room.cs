using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace HotelManager.Model
{
    public class Room
    {
        [Required]
        public int Id { get; set; }

        [Required]
        public byte Number { get; set; }

        public bool IsAvailable { get; set; }

        public bool IsDeleted { get; set; }

        public RoomCategory Category { get; set; }

        public byte Floor { get; set; }

        public byte SingleBeds { get; set; }

        public byte DoubleBeds { get; set; }

        public byte NumberOfBedrooms { get; set; }

        public byte NumberOfBaths { get; set; }

        public List<Amenity> Amenities { get; set; }

        [StringLength(500)]
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
