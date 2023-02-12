import java.util.*;
import java.io.*;

public class InputGenerator
{
	public static void main(String[] klein)
	{
		final int limM = 10000; //Max number of edges
		final Random rnd = new Random();
		final PrintWriter out = new PrintWriter(System.out);

		final int N = 1 + rnd.nextInt(800);
		//out.println(N);

		final int[] p = new int[N];
		for(int i = 0; i<N; i++) p[i] = i+1;

		if(N*(N-1)/2 <= limM)
		{
			for(int i = 0; i<N; i++)
			{
				int idx = rnd.nextInt(i+1);
				int swap = p[idx];
				p[idx] = p[i]; p[i] = swap;
			}
		}
		else
		{
			int m = 0;
			for(int i = 0; i<1000000 && m<limM; i++)
			{
				int idx = rnd.nextInt(N-1);
				int swap = p[idx];
				if(swap<p[idx+1]) ++m; else --m;
				p[idx] = p[idx+1]; p[idx+1] = swap;
			}
		}

		LinkedList<int[]> crs = new LinkedList<int[]>();
		for(int i = 0; i<N; i++)
			for(int j = 0; j<i; j++)
				if(p[j]>p[i])
					crs.add(new int[]{p[i],p[j]});

		out.println(N + " " + crs.size());
		for(int[] v : crs) out.println(v[0] + " " + v[1]);
		out.close();
	}
}
