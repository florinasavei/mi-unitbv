using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
namespace SearchingFileInWPF
{
    public class MyFolder
    {
        public string Name { get; set; }
        public string FullName { get; set; }
        public bool Searched { get; set; }

        public MyFolder()
        {
            this.Searched = false;
        }
    }
}
