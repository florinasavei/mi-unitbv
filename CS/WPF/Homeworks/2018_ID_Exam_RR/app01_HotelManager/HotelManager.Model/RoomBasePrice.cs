using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManager.Model
{
    public class RoomBasePrice
    {
        [Required]
        public int Id { get; set; }

        public DateTime PriceFrom { get; set; }

        public DateTime PriceUntil { get; set; }

        public Decimal PricePerPeriod { get; set; }

    }
}
