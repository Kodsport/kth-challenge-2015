public class KleinLog
{
	public static void main(String[] klein)
	{
		final long n = new java.util.Scanner(System.in).nextLong();
		System.out.println(1 + rek(n-1,0));
	}

	static final int maxlog = 63;
	static final long[][] cnt = new long[maxlog][maxlog];
	static final long[] sum = new long[maxlog];
	static
	{
		cnt[0][1] = 1; sum[0] = 2;
		for(int i = 1; i<maxlog; i++)
			for(int pow = 1; pow<maxlog; pow++)
				sum[i] += (cnt[i][pow] = cnt[i-1][pow] + cnt[i-1][pow-1])*(1L<<pow);
	}
	static long rek(final long n, final int i)
	{
		if(n==0) return 0;
		if((1L<<i)<=n) return sum[i] + rek(n-(1L<<i), i+1);
		if((1L<<i-1)<=n) return sum[i-1] + 2*rek(n-(1L<<i-1), i-1);
		else return rek(n, i-1);
	}
}
