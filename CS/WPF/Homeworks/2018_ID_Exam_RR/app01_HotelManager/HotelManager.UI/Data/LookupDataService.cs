using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Threading.Tasks;
using HotelManager.DAL;
using HotelManager.Model;

namespace HotelManager.UI.Data
{
    public class LookupDataService : IRoomLookupDataService
    {
        private Func<HotelManagerDbContext> _contextCreator;

        public LookupDataService(Func<HotelManagerDbContext> contextCreator)
        {
            _contextCreator = contextCreator;
        }

        public async Task<IEnumerable<LookupItem>> GetRoomLookupAsync()
        {
            using (var ctx = _contextCreator())
            {
                return await ctx.Rooms.AsNoTracking().
                    Select(f =>
                    new LookupItem
                    {
                        Id = f.Id,
                        DisplayMember = "Room Number " + f.Number.ToString()
            }).ToListAsync();
        }
    }

}
}
