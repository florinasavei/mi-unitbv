using Autofac;
using HotelManager.UI.Data;
using HotelManager.UI.ViewModel;

namespace HotelManager.UI.Startup
{
    public class Bootstrapper
    {
        public IContainer Bootstrap()
        {
            var builder = new ContainerBuilder();
            builder.RegisterType<MainWindow>().AsSelf();
            builder.RegisterType<MainViewModel>().AsSelf();
            builder.RegisterType<RoomDataService>().As<IRoomDataService>();

            return builder.Build();
        }
    }
}
