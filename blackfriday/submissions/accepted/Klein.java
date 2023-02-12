import java.util.*;
import java.io.*;

public class Klein
{
	public static void main(String[] klein)
	{
		final Scanner in = new Scanner(new BufferedInputStream(System.in));

		final int[] cnt = new int[7], idx = new int[7];
		final int n = in.nextInt();
		for(int i = 1; i<=n; i++)
		{
			final int die = in.nextInt();
			cnt[die]++; idx[die] = i;
		}

		for(int i = 6; i>0; i--)
			if(cnt[i]==1)
			{
				System.out.println(idx[i]);
				return;
			}
		System.out.println("none");
	}
}
