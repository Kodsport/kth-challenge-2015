//Solution by lukasP (Lukáš Poláček)
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Problem
{
    static void rem(int u, int v, List<int> p, List<Dictionary<int, int>> g)
    {
        Console.WriteLine((u + 1) + " " + (v + 1));
        g[u][v]--; g[v][u]--;
        if (g[u][v] == 0) g[u].Remove(v);
        if (g[v][u] == 0) g[v].Remove(u);
        p[u]--; p[v]--;
    }

    static void ad(int u, int v, List<int> p, List<Dictionary<int, int>> g)
    {
        if (g[u].ContainsKey(v)) g[u][v]++;
        else g[u].Add(v, 1);
        p[u]++;
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        int n = int.Parse(reader.ReadLine());
        List<Dictionary<int, int>> g = Enumerable.Range(0, n)
            .Select(x => new Dictionary<int, int> ()).ToList();

        List<int> p = Enumerable.Repeat(0, n).ToList();
        for (int i = 0; i < n; i++)
        {
            string[] ss = reader.ReadLine().Split();
            int a = int.Parse(ss[0]) - 1, b = int.Parse(ss[1]) - 1;
            ad(a, b, p, g);
            ad(b, a, p, g);
        }

        for (Queue<int> q = new Queue<int> (Enumerable.Range(0, n).Where(x => p[x] == 1));
            q.Count > 0; )
        {
            int u = q.Dequeue(), v = g[u].Keys.First();
            rem(u, v, p, g);
            if (p[v] == 1)
                q.Enqueue(v);
        }

        foreach (int k in Enumerable.Range(0, n).Where(x => p[x] == 2))
        {
            int u = g[k].Keys.First(), v = k;
            rem(u, v, p, g);

            while (u != k)
            {
                v = u; u = g[u].Keys.First();
                rem(u, v, p, g);
            }
        }
    }
}
