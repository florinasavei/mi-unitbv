using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManager.Model
{
    public class User
    {
        [Required]
        public int Id { get; set; }

        public  UserType UserType { get; set; }

        public string Email { get; set; }

        public string Username { get; set; }

        public string Password { get; set; }

        public string FirstName { get; set; }

        public string LastName { get; set; }

    }

    public enum UserType  {
        Superuser,
        Administrator,
        Employee,
        Client
    }
}
