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

        string[] ss = reader.ReadLine().Split();
        int n = int.Parse(ss[0]), m = int.Parse(ss[1]);

        List<int> pos = Enumerable.Range(0, n).ToList();

        for (int i = 0; i < m; i++)
        {
            ss = reader.ReadLine().Split();
            int a = int.Parse(ss[0]), b = int.Parse(ss[1]);
            if (a > b)
            {
                int tmp = a;
                a = b;
                b = tmp;
            }
            a--; b--;

            pos[a]++;
            pos[b]--;
        }

        List<int> best = Enumerable.Repeat(1, n).ToList();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++) if (pos[j] > pos[i])
                best[i] = Math.Max(best[i], best[j] + 1);

        Console.WriteLine(best.Max());
    }
}
