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

        public bool IsActive { get; set; }

        public bool IsDeleted { get; set; }

        [StringLength(50)]
        public string Email { get; set; }

        [StringLength(50)]
        public string Username { get; set; }

        [StringLength(50)]
        public string Password { get; set; }

        [StringLength(50)]
        public string FirstName { get; set; }

        [StringLength(50)]
        public string LastName { get; set; }

    }

    public enum UserType  {
        Superuser,
        Administrator,
        Employee,
        Client
    }
}
