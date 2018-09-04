using HotelManager.Model;

namespace HotelManager.DAL.Migrations
{
    using System;
    using System.Data.Entity;
    using System.Data.Entity.Migrations;
    using System.Linq;

    internal sealed class Configuration : DbMigrationsConfiguration<HotelManager.DAL.HotelManagerDbContext>
    {
        public Configuration()
        {
            AutomaticMigrationsEnabled = false;
        }

        protected override void Seed(HotelManager.DAL.HotelManagerDbContext context)
        {
            context.Users.AddOrUpdate(
                f => f.Username,
                new User { UserType = UserType.Administrator, Email = "admin@grr.la", Username = "admin" },
                new User { UserType = UserType.Employee, Email = "sam@grr.la", Username = "sam" },
                new User { UserType = UserType.Employee, Email = "marry@grr.la", Username = "marry" }
            );

            context.RoomBasePrices.AddOrUpdate(
                f => f.PriceFrom,
                new RoomBasePrice { PriceFrom = new DateTime(2018, 1, 1), PriceUntil = new DateTime(2018, 4, 30), PricePerPeriod = 80M },
                new RoomBasePrice { PriceFrom = new DateTime(2018, 4, 30), PriceUntil = new DateTime(2018, 9, 30), PricePerPeriod = 99M },
                new RoomBasePrice { PriceFrom = new DateTime(2018, 9, 30), PriceUntil = new DateTime(2018, 12, 31), PricePerPeriod = 89M }
                );

            context.Amenities.AddOrUpdate(
                f => f.Name,
                new Amenity { Name = "Balcony" },
                new Amenity { Name = "Garden View" },
                new Amenity { Name = "Mini-Fridge" }
                );

            context.Rooms.AddOrUpdate(
                f=> f.Number,
                new Room { Number = 1, Category = RoomCategory.Standard, Floor = 0, SingleBeds=0, DoubleBeds=1, NumberOfBedrooms=1, NumberOfBaths=1 },
                new Room { Number = 2, Category = RoomCategory.Economy, Floor = 0, SingleBeds=2, DoubleBeds=0, NumberOfBedrooms=1, NumberOfBaths=1 },
                new Room { Number = 3, Category = RoomCategory.Standard, Floor = 0, SingleBeds=0, DoubleBeds=1, NumberOfBedrooms=1, NumberOfBaths=1 }
                );

        }
    }
}
