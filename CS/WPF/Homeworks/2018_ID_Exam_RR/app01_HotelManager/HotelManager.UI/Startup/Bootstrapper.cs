using Autofac;
using HotelManager.DAL;
using HotelManager.UI.Data;
using HotelManager.UI.ViewModel;
using Prism.Events;

namespace HotelManager.UI.Startup
{
    public class Bootstrapper
    {
        public IContainer Bootstrap()
        {
            var builder = new ContainerBuilder();

            builder.RegisterType<HotelManagerDbContext>().AsSelf();
            builder.RegisterType<EventAggregator>().As<IEventAggregator>().SingleInstance();

            builder.RegisterType<MainWindow>().AsSelf();
            builder.RegisterType<MainViewModel>().AsSelf();
            builder.RegisterType<NavigationViewModel>().As<INavigationViewModel>();
            builder.RegisterType<RoomDetailViewModel>().As<IRoomDetailViewModel>();

            builder.RegisterType<LookupDataService>().AsImplementedInterfaces();
            builder.RegisterType<RoomDataService>().As<IRoomDataService>();
            return builder.Build();
        }
    }
}
