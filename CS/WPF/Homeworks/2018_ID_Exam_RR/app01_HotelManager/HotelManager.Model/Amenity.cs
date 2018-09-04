using System.ComponentModel.DataAnnotations;

namespace HotelManager.Model
{
    public class Amenity
    {
        [Required]
        public int Id { get; set; }

        [StringLength(50)]
        public string Name { get; set; }

        [StringLength(300)]
        public string Description { get; set; }

    }
}
