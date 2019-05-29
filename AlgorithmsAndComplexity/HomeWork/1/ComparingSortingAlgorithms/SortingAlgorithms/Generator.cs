using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortingAlgorithms
{
    public static class Generator
    {
        public static List<int> GenerateRandomNumbers(int length)
        {
            List<int> randomNumbers = new List<int>();
            Random random = new Random();

            for (int i = 0; i < length; i++)
            {
                randomNumbers.Add(random.Next());
            }

            return randomNumbers;
        }

        public static List<List<int>> GenerateSetOfRandomNumbers(int nrOfSets, int sizeOfSet)
        {
            var result = new List<List<int>>();

            for (int i = 0; i < nrOfSets; i++)
            {
                result.Add(GenerateRandomNumbers(sizeOfSet));
            }

            return result;
        }
    }
}
