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

        public async Task SaveAsync(Room friend)
        {
            using (var ctx = _contextCreator())
            {
                ctx.Rooms.Attach(friend);
                ctx.Entry(friend).State = EntityState.Modified;
                await ctx.SaveChangesAsync();
            }
        }

    }
}
