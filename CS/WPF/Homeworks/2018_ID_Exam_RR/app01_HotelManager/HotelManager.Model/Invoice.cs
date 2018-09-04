using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManager.Model
{
    public class Invoice
    {
        [Required]
        public int Id { get; set; }

        public DateTime InvoiceDate { get; set; }

        public List<Reservation> Reservations { get; set; }

        public List<SelectedService> SelectedServices { get; set; }

        public decimal PriceForRooms { get; set; }

        public decimal PriceForServices { get; set; }

        public decimal TotalAmount { get; set; }

        public decimal PayedAmount { get; set; }

    }
}
