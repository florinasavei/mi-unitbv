using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Threading.Tasks;
using HotelManager.Model;
using HotelManager.DAL;

namespace HotelManager.UI.Data
{
    public class RoomDataService : IRoomDataService
    {
        private Func<HotelManagerDbContext> _contextCreator;

        public RoomDataService(Func<HotelManagerDbContext> contextCrator)
        {
            _contextCreator = contextCrator;

        }

        public async Task<Room> GetByIdAsync(int friendId)
        {
            using (var ctx = _contextCreator())
            {
                return await ctx.Rooms.AsNoTracking().SingleAsync(f => f.Id == friendId);
            }
        }
    }
}
