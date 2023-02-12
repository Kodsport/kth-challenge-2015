//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Globalization;
using System.Threading;

class Problem
{
    public static void Main ()
    {
        Thread.CurrentThread.CurrentCulture = System.Globalization.CultureInfo.InvariantCulture;
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        int n = int.Parse(reader.ReadLine());
        var a = reader.ReadLine().Split().Select(x => int.Parse(x));

        double len = Math.Pow(2, -3 / 4.0);

        double res = 0;
        long need = 1;
        foreach (int x in a)
        {
            need *= 2;
            res += len * ((need + 1) / 2);
            need -= x;
            if (need <= 0)
                break;

            len /= Math.Sqrt(2);
        }

        if (need > 0)
            Console.WriteLine("impossible");
        else
            Console.WriteLine(res.ToString("F10"));
    }
}
