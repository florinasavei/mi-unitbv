using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortingAlgorithms
{
    class Program
    {
        static void Main(string[] args)
        {
            List<List<List<int>>> setOfRandomNumbers = new List<List<List<int>>>
            {
                Generator.GenerateSetOfRandomNumbers(3, 100_000),
                Generator.GenerateSetOfRandomNumbers(3, 300_000),
                Generator.GenerateSetOfRandomNumbers(3, 600_000)
            };



        }
    }
}
