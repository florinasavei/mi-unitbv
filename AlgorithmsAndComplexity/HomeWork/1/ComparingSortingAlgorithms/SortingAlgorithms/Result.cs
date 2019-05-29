using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortingAlgorithms
{
    public class SortingResult
    {
        public string SortMethod { get; set; }
        public List<List<List<int>>> UnsortedDataSet { get; set; }
        public List<List<List<int>>> SortedDataSet { get; set; }
        public TimeSpan Duration { get; set; }
    }
}
