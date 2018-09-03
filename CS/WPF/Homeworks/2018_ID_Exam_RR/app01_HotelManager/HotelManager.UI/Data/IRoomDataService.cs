using System.Collections.Generic;
using HotelManager.Model;

namespace HotelManager.UI.Data
{
    public interface IRoomDataService
    {
        IEnumerable<Room> GetAll();
    }
}