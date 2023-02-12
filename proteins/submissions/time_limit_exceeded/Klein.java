import java.util.*;
import java.io.*;

public class Klein
{
	static final int[] dp = new int[5 * 5000 * 5000];
	static char[] w;
	//prev: 0 = none/C/G/T, 1 = A, 2 = AT
	static int rek(final int prev, final int mod, final int i, final int len, final int n)
	{
		if(n==0) return 0;
		if(i>=len)
		{
			if(prev==0) return (3-mod)%3 + 3*n;
			if(prev==1) return 2 + 3*(n-1);
			if(prev==2) return 1 + 3*(n-1);
		}

		final int state = mod==0 ? 0 : prev==1 ? 1 : prev==2 ? 2 : 2+mod;
		final int idx = state*5000*5000 + i*5000 + n-1;
		if(dp[idx]!=0) return dp[idx];

		if(mod==0 && w[i]=='A') return dp[idx] = rek(1,1,i+1,len,n);
		if(prev==1 && w[i]=='T') return dp[idx] = rek(2,2,i+1,len,n);
		if(prev==2 && w[i]=='G') return dp[idx] = rek(0,0,i+1,len,n-1);

		if(prev==0 && w[i]=='C') return dp[idx] = rek(0, (mod+1)%3, i+1, len, n);

		int sum = n*3;
		if(mod==0) sum = 1 + rek(1,1,i,len,n);
		if(prev==1) sum = 1 + rek(2,2,i,len,n);
		if(prev==2) sum = 1 + rek(0,0,i,len,n-1);
		return dp[idx] = Math.min(sum, rek(0,(mod+1)%3,i+1,len,n));
	}

	public static void main(String[] klein)
	{
		final Scanner in = new Scanner(new BufferedInputStream(System.in));

		final int n = in.nextInt();
		w = in.next().toCharArray();
		final int len = w.length;

		int min = 3*n;
		for(int i = 1; i<=Math.min(n,len); i++) min = Math.min(min, 3*(n-i) + rek(0,0,0,len,i));
		System.out.println(min);
	}
}
