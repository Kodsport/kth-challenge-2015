import java.util.*;

public class Kleinv3
{
	private static final Random rnd = new Random();
	private static final int p = 127; //x = a*x + b mod p
	private static final String[] move = {"rock", "paper", "scissors", "lizard", "Spock"};
	private static final int[][] lose = {{1,4}, {2,3}, {0,4}, {0,2}, {1,3}};

	private static final int[] mod5 = new int[p];
	static{ for(int i = 0; i<p;) for(int j = 0; i<p&&j<5; j++) mod5[i++] = j; }

	private static int getIndex(final String s)
	{
		final char c = s.charAt(0);
		return c=='r' ? 0 : c=='p' ? 1 : c=='s' ? 2 : c=='l' ? 3 : 4;
	}

	public static void main(String[] klein)
	{
		final Scanner in = new Scanner(System.in);
		final int R = in.nextInt();
//int xx = 42;
		System.out.println(move[rnd.nextInt(5)]); //System.err.println("Should output: "+move[(xx=(17*xx+23)%127)%5] + " " +xx);
		final int[] xmod = new int[R];
		xmod[0] = getIndex(in.next());
		System.out.println(move[rnd.nextInt(5)]); //System.err.println("Should output: "+move[(xx=(17*xx+23)%127)%5] + " " +xx);
		xmod[1] = getIndex(in.next());

		final int[] aa = new int[p], bb = new int[p], cc = new int[p];
		for(int x = xmod[0]; x<p; x+=5) cc[x] = bb[x] = xmod[1];
		boolean done = false;
		LinkedList<Rnd> qu = new LinkedList<Rnd>();

		for(int r = 2; r<R; r++)
		{
			for(; !done && qu.size()<(1<<19);) //Add time limit? Lower size limit?
				for(int x = xmod[0]; x<p; x+=5)
				{
					final int a = aa[x], b = bb[x], c = cc[x];//++;
					//if(b==p-1){ bb[x]=0; done = ++aa[x]==p; }
					bb[x] += 5; cc[x] += 5;
					if(bb[x]>=p)
					{
						done = ++aa[x]==p;
						cc[x] = aa[x]*x%p;
						bb[x] = xmod[1]-mod5[cc[x]];
						if(bb[x]<0) bb[x]+=5;
						cc[x] += bb[x];
					}
					if(cc[x]>=p){ cc[x]-=p; bb[x]+=xmod[1]-cc[x]; if(bb[x]<0) bb[x]+=5; cc[x]=xmod[1]; }

					boolean ok = true;
					int tmp = c;
					for(int i = 1; i<r && ok; i++, tmp = (a*tmp + b)%p) ok &= mod5[tmp]==xmod[i];
					if(ok) qu.add(new Rnd(a,b,tmp,r));
				}
//System.err.println("1: "+qu.size());
			loop:while(!qu.isEmpty())
			{
				Rnd tmp = qu.pop();
				if(tmp.r==r){ qu.add(tmp); break; }
				for(; tmp.r<r; tmp.r++, tmp.next()) if(mod5[tmp.x]!=xmod[tmp.r]) continue loop;
				qu.add(tmp);
			}
//System.err.println("2: "+qu.size()); if(qu.size()<7) System.err.println(qu);
			int cnt = qu.size();
			if(r>16 && cnt>=64) while(qu.size()*2>cnt) qu.pop(); //Remove duplicate states? =D
			cnt = 0;
			final int[] pr = new int[5];
			for(Rnd tmp : qu){ pr[mod5[tmp.x]]++; cnt++; }

			int i = 0;
			if(cnt==0) i = rnd.nextInt(5); //Remove?
			else
			{
				cnt = rnd.nextInt(cnt);
				while(cnt>=pr[i]) cnt -= pr[i++];
			}

			System.out.println(move[lose[i][rnd.nextInt(2)]]); //System.err.println("Should output: "+move[(xx=(17*xx+23)%127)%5] + " " +xx);
			xmod[r] = getIndex(in.next());
		}
	}

	private static class Rnd
	{
		final int a, b;
		int x, r;
		Rnd(int aa, int bb, int xx, int rr)
		{
			a = aa; b = bb; x = xx; r = rr;
		}

		int next()
		{
			return x = (a*x + b)%p;
		}
	}
}

