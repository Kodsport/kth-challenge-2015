import java.util.*;
import java.io.*;

public class Klein
{
	static final int[] cnt = new int[31];
	static final double[] w = new double[31], h = new double[31];
	static
	{
		w[2] = Math.pow(2, -5.0/4);
		h[2] = Math.pow(2, -3.0/4);
		for(int i = 3; i<=30; i++)
		{
			h[i] = w[i-1];
			w[i] = h[i-1]/2;
		}
	}
	private static double rek(final int i, final int req)
	{
		if(i>30) return Double.NaN;
		return req/2 * h[i] + (cnt[i]<req ? rek(i+1,req-cnt[i]<<1) : 0);
	}

	public static void main(String[] klein)
	{
		final Scanner in = new Scanner(new BufferedInputStream(System.in));

		final int n = in.nextInt();
		for(int i = 2; i<=n; i++) cnt[i] = in.nextInt();

		final double ans = rek(2,2);
		if(Double.isNaN(ans)) System.out.println("impossible");
		else System.out.println(ans);
	}
}
