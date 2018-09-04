using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HotelManager.Model;

namespace HotelManager.UI.Data
{
    public interface IRoomLookupDataService
    {
        Task<IEnumerable<LookupItem>> GetRoomLookupAsync();
    }
}
