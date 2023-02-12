import java.util.*;
import java.io.*;

//Fails test cases like this:
// ...
// .XX
public class Klein
{
	public static void main(String[] klein)
	{
		final Scanner in = new Scanner(new BufferedInputStream(System.in));

		final int n = in.nextInt(), m = in.nextInt();
		final boolean[][] g = new boolean[n][m];
		int black = 0;
		for(int i = 0; i<n; i++)
		{
			final char[] s = in.next().toCharArray();
			for(int j = 0; j<m; j++) black += ((g[i][j] = s[j]=='X') ? 1 : 0);
		}

		for(int i = 0; i<n; i++)
			for(int j = 0; j<m; j++)
				if(g[i][j] && m-j+(n-i-1)*Math.min(m,4)>=4)
				{
					for(int k = j; k<Math.min(j+4,m); k++)
						if(g[i][k] ^= true) ++black;
						else --black;
					for(int l = i+1, left = 4-Math.min(m-j,4); left>0; l++)
						for(int k = m-1; k>=0 && left>0; --left, --k)
							if(g[l][k] ^= true) ++black;
							else --black;
				}

		if(black!=0) System.out.print("im");
		System.out.println("possible");
	}
}
