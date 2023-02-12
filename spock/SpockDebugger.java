import java.util.*;
import java.io.*;

public class SpockDebugger
{
	private static final int p = 127; //x = a*x + b mod p
	private static final String[] move = {"rock", "paper", "scissors", "lizard", "Spock"};
	private static final int[][] lose = {{1,4}, {2,3}, {0,4}, {0,2}, {1,3}};

	private static int getIndex(final String s)
	{
		final char c = s.charAt(0);
		return c=='r' ? 0 : c=='p' ? 1 : c=='s' ? 2 : c=='l' ? 3 : 4;
	}

	private static void gobbleErr(final InputStream err) throws Exception
	{
		while(err.available()>0) System.err.write(err.read());
		System.err.flush();
	}

	public static void main(String[] arg) throws Exception
	{
		if(arg.length==0 || arg.length==1 && (arg[0].equals("-h") || arg[0].equals("--help") || arg[0].equals("-help")))
		{
			System.out.println("Usage of SpockDebugger");
			System.out.println("-------------------------------------------------");
			System.out.println("\nUsage:\n\tjava -jar SpockDebugger.jar \"[command to run your program]\" [options]");
			System.out.println("Options:\n\tr=[number of rounds to play, default value 20]\n\tx=[the initial state of the computer, default value 42]\n\ta=[the a value used by the computer, defualt value 17]\n\tb=[the b value used by the computer, default value 23]");
			System.out.println("The order of the parameters is irrelevant, but do \nnote that the command to run the program must be \nenclosed in quotes. Should any unknown parameter \noccur, behavior is undefined. The default values are\nthose stated in the sample interaction (but for 20 rounds).");
			System.out.println("\nExample (python):\n\tjava -jar SpockDebugger.jar \"python pathtosolution/mysolution.py\" r=30");
			System.out.println("Runs the provided python solution using the default \nvalues for 30 rounds.");
			System.out.println("\nExample (java):\n\tjava -jar SpockDebugger.jar \"java -cp pathtosolutiondirectory/ MySolution\" a=7 b=99 x=151 r=1000");
			System.out.println("Runs the provided java solution with main class in \nthe file 'pathtosolutiondirectory/MySolution.class' \nusing the provided values.");
			System.out.println("\nAdvice: Make sure that the command you provide as \nparameter to SpockDebugger can be run on its own.");
			return;
		}

		int R = 20, a = 17, b = 23, x = 42;
		String cmd = null;
		for(int i = 0; i<arg.length; i++)
			if(arg[i].startsWith("r=") || arg[i].startsWith("R=")) R = Integer.parseInt(arg[i].substring(2));
			else if(arg[i].startsWith("x=")) x = Integer.parseInt(arg[i].substring(2));
			else if(arg[i].startsWith("a=")) a = Integer.parseInt(arg[i].substring(2));
			else if(arg[i].startsWith("b=")) b = Integer.parseInt(arg[i].substring(2));
			else cmd = arg[i];


		System.out.printf("Initializing a game of %d rounds using x=%d, a=%d and b=%d.\n", R, x, a, b);
		System.out.printf("Running command: %s\n", cmd==null ? "No command found" : cmd);

		final Process pr = Runtime.getRuntime().exec(cmd);
		final PrintStream out = new PrintStream(pr.getOutputStream(), true);
		final Scanner in = new Scanner(pr.getInputStream());
		final InputStream err = pr.getErrorStream();

		System.out.println("Player is booted. Starting game...\n");
		gobbleErr(err);
		long time = System.currentTimeMillis();

		int wins = 0, draws = 0, losses = 0;
		out.println(R);
		for(int r = 1; r<=R; r++)
		{
			gobbleErr(err);
			String mv = in.next();
			gobbleErr(err);
			x = (x*a+b)%p;
			final int i = x%5, j = getIndex(mv);
			out.println(move[i]);

			if(lose[i][0]==j || lose[i][1]==j) wins++;
			else if(lose[j][0]==i || lose[j][1]==i) losses++;
			else draws++;
			
			System.out.printf("Round %d\nYou output: %s\nComputer output: %s (state x=%d)\n", r, mv, move[i], x);
			System.out.printf("Wins %d, Draws %d, Losses %d\n", wins, draws, losses);
			//gobbleErr(err);
			System.out.println("--------------------------\n");
		}

		time = System.currentTimeMillis() - time;
		gobbleErr(err);

		System.out.println("Win percentage: "+(double)wins/R);
		System.out.println("Draw percentage: "+(double)draws/R);
		System.out.println("Lose percentage: "+(double)losses/R);
		System.out.printf("\nTotal time: %.3f sec\n(Bear in mind that Kattis may be faster/slower and that this measurement includes some excessive I/O.)\n", time/1000.0);
	}
}
