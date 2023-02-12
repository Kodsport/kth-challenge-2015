//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        reader.ReadLine();
        var a = reader.ReadLine().Split().Select(x => int.Parse(x)).ToList();

        var b =
                from i in Enumerable.Range(0, a.Count)
                group i by a[i] into g
                where g.Count() == 1
                select new {Val = g.Key, Ind = g.First() + 1};

        if (b.Count() == 0)
            Console.WriteLine("none");
        else
            Console.WriteLine(b.First(y => y.Val == b.Max(x => x.Val)).Ind);
    }
}
