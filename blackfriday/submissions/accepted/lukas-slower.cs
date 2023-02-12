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

        var b = Enumerable.Range(0, a.Count).Where(x => a.Count(y => y == a[x]) == 1)
                .Select(x => new {Val = a[x], Ind = x + 1});

        if (b.Count() == 0)
            Console.WriteLine("none");
        else
            Console.WriteLine(b.First(y => y.Val == b.Max(x => x.Val)).Ind);
    }
}
