using System.Collections.Generic;
using System.Threading.Tasks;
using HotelManager.Model;

namespace HotelManager.UI.Data
{
    public interface IRoomDataService
    {
        Task<Room> GetByIdAsync(int roomId);
        Task SaveAsync(Room friend);
    }
}