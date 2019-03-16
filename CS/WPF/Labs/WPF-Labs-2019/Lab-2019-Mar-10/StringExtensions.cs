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

        public static List<int> GetNumbersFromString(this string s)
        {
            try
            {
                return new List<int>(Array.ConvertAll(s.Split(' '), int.Parse));
            }
            catch (Exception e)
            {
                throw new Exception(e.Message);
            }
        }

    }
}