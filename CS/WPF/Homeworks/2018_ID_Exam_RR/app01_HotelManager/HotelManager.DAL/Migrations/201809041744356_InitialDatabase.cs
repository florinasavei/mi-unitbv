namespace HotelManager.DAL.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class InitialDatabase : DbMigration
    {
        public override void Up()
        {
            CreateTable(
                "dbo.Amenity",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        Name = c.String(maxLength: 50),
                        Description = c.String(maxLength: 300),
                        Room_Id = c.Int(),
                    })
                .PrimaryKey(t => t.Id)
                .ForeignKey("dbo.Room", t => t.Room_Id)
                .Index(t => t.Room_Id);
            
            CreateTable(
                "dbo.User",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        UserType = c.Int(nullable: false),
                        IsActive = c.Boolean(nullable: false),
                        IsDeleted = c.Boolean(nullable: false),
                        Email = c.String(maxLength: 50),
                        Username = c.String(maxLength: 50),
                        Password = c.String(maxLength: 50),
                        FirstName = c.String(maxLength: 50),
                        LastName = c.String(maxLength: 50),
                        ClinetDiscount = c.Byte(),
                        Discriminator = c.String(nullable: false, maxLength: 128),
                    })
                .PrimaryKey(t => t.Id);
            
            CreateTable(
                "dbo.Invoice",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        IsDeleted = c.Boolean(nullable: false),
                        InvoiceDate = c.DateTime(nullable: false),
                        PriceForRooms = c.Decimal(nullable: false, precision: 18, scale: 2),
                        PriceForServices = c.Decimal(nullable: false, precision: 18, scale: 2),
                        Discount = c.Decimal(nullable: false, precision: 18, scale: 2),
                        TotalAmount = c.Decimal(nullable: false, precision: 18, scale: 2),
                        PayedAmount = c.Decimal(nullable: false, precision: 18, scale: 2),
                        Client_Id = c.Int(),
                    })
                .PrimaryKey(t => t.Id)
                .ForeignKey("dbo.User", t => t.Client_Id)
                .Index(t => t.Client_Id);
            
            CreateTable(
                "dbo.Reservation",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        Status = c.Int(nullable: false),
                        IsDeleted = c.Boolean(nullable: false),
                        ReservedFrom = c.DateTime(nullable: false),
                        ReservedUntil = c.DateTime(nullable: false),
                        NumberOrPeople = c.Byte(nullable: false),
                        NumberOfDays = c.Int(nullable: false),
                        PricePerReservation = c.Decimal(nullable: false, precision: 18, scale: 2),
                        Comment = c.String(maxLength: 500),
                        Invoice_Id = c.Int(),
                        Client_Id = c.Int(),
                    })
                .PrimaryKey(t => t.Id)
                .ForeignKey("dbo.Invoice", t => t.Invoice_Id)
                .ForeignKey("dbo.User", t => t.Client_Id)
                .Index(t => t.Invoice_Id)
                .Index(t => t.Client_Id);
            
            CreateTable(
                "dbo.Room",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        Number = c.Byte(nullable: false),
                        IsAvailable = c.Boolean(nullable: false),
                        IsDeleted = c.Boolean(nullable: false),
                        Category = c.Int(nullable: false),
                        Floor = c.Byte(nullable: false),
                        SingleBeds = c.Byte(nullable: false),
                        DoubleBeds = c.Byte(nullable: false),
                        NumberOfBedrooms = c.Byte(nullable: false),
                        NumberOfBaths = c.Byte(nullable: false),
                        Description = c.String(maxLength: 500),
                    })
                .PrimaryKey(t => t.Id);
            
            CreateTable(
                "dbo.RoomBasePrice",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        PriceFrom = c.DateTime(nullable: false),
                        PriceUntil = c.DateTime(nullable: false),
                        PricePerPeriod = c.Decimal(nullable: false, precision: 18, scale: 2),
                        Room_Id = c.Int(),
                    })
                .PrimaryKey(t => t.Id)
                .ForeignKey("dbo.Room", t => t.Room_Id)
                .Index(t => t.Room_Id);
            
            CreateTable(
                "dbo.SelectedService",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        ServiceFrom = c.DateTime(nullable: false),
                        ServiceUntill = c.DateTime(nullable: false),
                        Service_Id = c.Int(),
                        Invoice_Id = c.Int(),
                    })
                .PrimaryKey(t => t.Id)
                .ForeignKey("dbo.Service", t => t.Service_Id)
                .ForeignKey("dbo.Invoice", t => t.Invoice_Id)
                .Index(t => t.Service_Id)
                .Index(t => t.Invoice_Id);
            
            CreateTable(
                "dbo.Service",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                        ServiceName = c.String(maxLength: 100),
                        Description = c.String(maxLength: 500),
                        PricePerDay = c.Decimal(nullable: false, precision: 18, scale: 2),
                    })
                .PrimaryKey(t => t.Id);
            
            CreateTable(
                "dbo.RoomReservation",
                c => new
                    {
                        Room_Id = c.Int(nullable: false),
                        Reservation_Id = c.Int(nullable: false),
                    })
                .PrimaryKey(t => new { t.Room_Id, t.Reservation_Id })
                .ForeignKey("dbo.Room", t => t.Room_Id, cascadeDelete: true)
                .ForeignKey("dbo.Reservation", t => t.Reservation_Id, cascadeDelete: true)
                .Index(t => t.Room_Id)
                .Index(t => t.Reservation_Id);
            
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.Reservation", "Client_Id", "dbo.User");
            DropForeignKey("dbo.Invoice", "Client_Id", "dbo.User");
            DropForeignKey("dbo.SelectedService", "Invoice_Id", "dbo.Invoice");
            DropForeignKey("dbo.SelectedService", "Service_Id", "dbo.Service");
            DropForeignKey("dbo.Reservation", "Invoice_Id", "dbo.Invoice");
            DropForeignKey("dbo.RoomBasePrice", "Room_Id", "dbo.Room");
            DropForeignKey("dbo.RoomReservation", "Reservation_Id", "dbo.Reservation");
            DropForeignKey("dbo.RoomReservation", "Room_Id", "dbo.Room");
            DropForeignKey("dbo.Amenity", "Room_Id", "dbo.Room");
            DropIndex("dbo.RoomReservation", new[] { "Reservation_Id" });
            DropIndex("dbo.RoomReservation", new[] { "Room_Id" });
            DropIndex("dbo.SelectedService", new[] { "Invoice_Id" });
            DropIndex("dbo.SelectedService", new[] { "Service_Id" });
            DropIndex("dbo.RoomBasePrice", new[] { "Room_Id" });
            DropIndex("dbo.Reservation", new[] { "Client_Id" });
            DropIndex("dbo.Reservation", new[] { "Invoice_Id" });
            DropIndex("dbo.Invoice", new[] { "Client_Id" });
            DropIndex("dbo.Amenity", new[] { "Room_Id" });
            DropTable("dbo.RoomReservation");
            DropTable("dbo.Service");
            DropTable("dbo.SelectedService");
            DropTable("dbo.RoomBasePrice");
            DropTable("dbo.Room");
            DropTable("dbo.Reservation");
            DropTable("dbo.Invoice");
            DropTable("dbo.User");
            DropTable("dbo.Amenity");
        }
    }
}
