using System.Data.Entity;
using System.Data.Entity.ModelConfiguration.Conventions;
using HotelManager.Model;

namespace HotelManager.DAL
{
    public class HotelManagerDbContext : DbContext
    {
        public HotelManagerDbContext() : base("HotelManagerDb")
        {

        }

        public DbSet<User> Users { get; set; }
        public DbSet<Client> Clients { get; set; }
        public DbSet<RoomBasePrice> RoomBasePrices { get; set; }
        public DbSet<Amenity> Amenities { get; set; }
        public DbSet<Room> Rooms { get; set; }
        public DbSet<Reservation> Reservations { get; set; }
        public DbSet<Service> Services { get; set; }
        public DbSet<SelectedService> SelectedServices { get; set; }
        public DbSet<Invoice> Invoices { get; set; }

        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            modelBuilder.Conventions.Remove<PluralizingTableNameConvention>();
        }

    }
}
