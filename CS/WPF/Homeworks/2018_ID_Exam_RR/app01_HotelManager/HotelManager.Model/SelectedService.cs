using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManager.Model
{
    public class SelectedService
    {
        [Required]
        public int Id { get; set; }

        public uint NumberOfDays { get; set; }

        public Service Service { get; set; }

        public DateTime ServiceFrom { get; set; }

        public DateTime ServiceUntill { get; set; }

    }
}
