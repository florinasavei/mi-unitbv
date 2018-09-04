using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManager.Model
{
    public class Client : User
    {
        [Required]
        public int Id { get; set; }

        public bool IsActive { get; set; }

        public bool IsDeleted { get; set; }

        public byte ClinetDiscount { get; set; }

        public List<Reservation> Reservations { get; set; }

        public List<Invoice> Invoices { get; set; }

    }
}
