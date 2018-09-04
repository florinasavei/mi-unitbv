using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManager.Model
{
    public class Service
    {
        [Required]
        public int Id { get; set; }

        [StringLength(100)]
        public string ServiceName { get; set; }

        [StringLength(500)]
        public string Description { get; set; }

        public Decimal PricePerDay { get; set; }

    }
}
