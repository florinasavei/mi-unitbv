using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HotelManager.Model;

namespace HotelManager.UI.Data
{
    class RoomDataService : IRoomDataService
    {
        public IEnumerable<Room> GetAll()
        {
            yield return new Room {Number = 10};
            yield return new Room {Number = 20};
        }
    }
}
