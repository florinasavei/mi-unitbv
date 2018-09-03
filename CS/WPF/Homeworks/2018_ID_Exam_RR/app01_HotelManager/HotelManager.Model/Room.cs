using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManager.Model
{
    public class Room
    {
        public int RoomId { get; set; }
        public int Number { get; set; }
        public int Floor { get; set; }
        public decimal Price { get; set; }
        public List<Reservation> Reservations { get; set; }
    }
}
