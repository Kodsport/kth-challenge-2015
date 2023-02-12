//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections;
using System.Linq;

class Problem
{
    public static void Main ()
    {
        long n = long.Parse(Console.ReadLine());
        long q = 1L << 32;
        BitArray b = new BitArray(new int[]{(int)(n % q), (int)(n / q)});

        long res = 0;
        int cnt = Enumerable.Range(0, 60).Count(x => b[x]);
        for (long i = 0, p3 = 1; i < 37; i++, p3 *= 3)
            if (b[(int)i])
                res += (1L << --cnt) * p3;
        Console.WriteLine(res);
    }
}
