import java.util.*;
import java.io.*;

public class Klein
{
	public static void main(String[] klein)
	{
		final Scanner in = new Scanner(new BufferedInputStream(System.in));
		final PrintWriter out = new PrintWriter(System.out);

		final int N = in.nextInt();
		final int[] deg = new int[N+1];
		final Edge[] g = new Edge[N+1];
		for(int i = 0; i<N; i++)
		{
			final int a = in.nextInt(), b = in.nextInt();
			deg[a]++; deg[b]++;
			g[a] = new Edge(b, g[a]);
			g[b] = new Edge(a, g[b]);
		}

		final boolean[] vis = new boolean[N+1];
		final int[] qu = new int[N];
		int back = 0;
		for(int i = 1; i<=N; i++) if(deg[i]==1) qu[back++] = i;
		while(back>0)
		{
			final int v = qu[--back];
			vis[v] = true;
			for(Edge e = g[v]; ; e=e.nxt)
				if(!vis[e.to])
				{
					out.println(v + " " + e.to);
					if(--deg[e.to]==1) qu[back++] = e.to;
					break;
				}
		}

		for(int i = 1; i<=N; i++)
			if(!vis[i])
			{
				final int start = i;
				for(int j = i, nxt = -1; nxt!=start; j = nxt)
				{
					vis[j] = true;
					for(Edge e = g[j]; e!=null; e=e.nxt) if(!vis[e.to]) nxt = e.to;
					if(nxt==j) nxt = start;
					out.println(j + " " + nxt);
				}
			}

		out.close();
	}

	private static class Edge
	{
		final int to; final Edge nxt;
		Edge(int t, Edge n)
		{
			to = t; nxt = n;
		}
	}
}
