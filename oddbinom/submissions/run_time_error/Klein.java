import java.util.*;

public class Klein
{
	public static void main(String[] klein)
	{
		final int n = new Scanner(System.in).nextInt();

		long sum = 1;
		final long[] cnt = new long[n];
		cnt[0] = 1;
		for(int pow = 1, nxt = 1; nxt<n; pow*=2)
			for(int i = 0; nxt<n && i<pow; i++)
				sum += cnt[nxt++] = cnt[i]*2;

		System.out.println(sum);
	}
}
