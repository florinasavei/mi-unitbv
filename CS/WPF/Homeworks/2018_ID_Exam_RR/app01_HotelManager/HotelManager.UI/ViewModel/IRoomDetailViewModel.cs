using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManager.UI.ViewModel
{
    public interface IRoomDetailViewModel
    {
        Task LoadAsync(int roomId);
    }
}
