using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab_2019_Mar_10
{
    public static class StringExtensions
    {
        public static bool IsPalindrom(this string value)
        {
            string myString = value.ToLower();
            string reversedString = new string(myString.Reverse().ToArray());
            return string.CompareOrdinal(myString, reversedString) == 0;
        }

        public static List<int> SplitStringIntoNumbers(this string s)
        {
            s = s.Trim();

            string[] splitedString = s.Split(' ');

            var result = new List<int>();

            foreach (var word in splitedString)
            {
                bool parseSuccess = int.TryParse(word, out int intResult);
                if (!parseSuccess)
                {
                    return null;
                }
                result.Add(intResult);
            }

            return result;
        }

        public static int CountDistinctLetters(this string s)
        {
            return s.Distinct().Count();
        }

    }
}