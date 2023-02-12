import java.util.*;
import java.io.*;

public class Klein
{
	public static void main(String[] klein)
	{
		final Scanner in = new Scanner(new BufferedInputStream(System.in));

		final int N = in.nextInt();
		final int[] pos = new int[N];
		for(int i = 0; i<N; i++) pos[i] = i;

		for(int m = in.nextInt(); m>0; m--)
		{
			final int a = in.nextInt()-1, b = in.nextInt()-1;
			pos[a]++; pos[b]--;
		}

		final int[] lds = new int[N+1];
		int len = 0;
		for(int i = 0; i<N; i++)
		{
			int nxt = len;
			while(nxt>0 && pos[i]>=lds[nxt-1]) --nxt; //This part can be optimized to O(log n).
			lds[nxt] = pos[i];
			if(nxt==len) ++len;
		}

		System.out.println(len);
	}
}
