using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sharpkick
{
    class StringPointerUtils
    {
        unsafe public static string GetAsciiString(byte* pChars, int max = 255)
        {
            int length;
            for (length = 0; *(pChars + length) != 0 && length < 255; length++) ;

            if (length == 0) return string.Empty;

            fixed (char* pResult = new char[length])
            {
                ASCIIEncoding.Default.GetChars(pChars, length, pResult, length);
                return new string(pResult);
            }
        }

    }
}
