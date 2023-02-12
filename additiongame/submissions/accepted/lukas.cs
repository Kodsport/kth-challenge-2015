//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;

class Problem
{
    static int n;
    static List<int> a, b, c, pb;
    static String Print(List<int> a, List<int> p)
    {
        return String.Join(" ", Enumerable.Range(0, n).Select(x => a[p[x]]).Select(y => (y == 0 ? n : y)));
    }
    static void swap(List<int> x, int i, int j)
    {
        int tmp = x[i];
        x[i] = x[j];
        x[j] = tmp;
    }
    static void fix(int j, int nj)
    {
        while (true)
        {
            HashSet<int> w = new HashSet<int>(new int[]{c[j], c[nj]});
            int alt1 = (j + b[j]) % n;
            int alt2 = (j + b[nj]) % n;
            if (w.Contains(alt1) || w.Contains(alt2))
            {
                int res = w.Contains(alt1) ? alt1 : alt2;
                if (res == alt2)
                {
                    swap(b, j, nj);
                    swap(pb, j, nj);
                }
                if (c[nj] == res)
                    swap(c, j, nj);
                return;
            }

            int sol = (n + c[j] - b[j]) % n;
            swap(b, j, sol);
            swap(pb, j, sol);
            swap(c, j, sol);
            swap(c, j, nj);
        }
    }
    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);
        n = int.Parse(reader.ReadLine());

        a = Enumerable.Range(0, n).ToList();
        b = Enumerable.Repeat(0, n).ToList();
        c = Enumerable.Range(0, n).ToList();
        List <int> d = reader.ReadLine().Split().Select(x => int.Parse(x)).ToList();
        if (d.Sum() % n != 0)
        {
            Console.WriteLine("impossible");
            return;
        }

        pb = Enumerable.Range(0, n).ToList();
        List<int> ipb = Enumerable.Repeat(0, n).ToList();

        int s = 0;
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n; j++)
                ipb[pb[j]] = j;
            s = (s + d[i]);
            b[ipb[i]] = d[i];
            b[ipb[i + 1]] = (n - s) % n;
            fix(ipb[i], ipb[i + 1]);
        }

        for (int i = 0; i < n; i++)
            Debug.Assert((a[i] + b[i]) % n == c[i]);
        for (int j = 0; j < n; j++)
            ipb[pb[j]] = j;

        Console.WriteLine(Print(a.Select(x => (n - x) % n).ToList(), ipb));
        Console.WriteLine(Print(c, ipb));
    }
}
