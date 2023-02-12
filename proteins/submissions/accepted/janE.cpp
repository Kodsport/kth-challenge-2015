#include <iostream>
#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
int main(){
	static int dp[1005][1005];//#matches -> cost
	int k; cin >> k;
	string s; cin >> s;
	int n=(int)s.size();
	fill(dp[0],dp[0]+n+1,1e9);
	dp[0][0]=0;
	for(int i=0;i<n;i++){
		fill(dp[i+1],dp[i+1]+n+1,1e9);
		// s[i] part of a match
		for(int v=1;v<=i+1;v++){
			int match;
			if(s[i]=='C')continue;else
			if(s[i]=='A')dp[i+1][v]=min(dp[i+1][v],dp[i][v-1]+2);else
			if(s[i]=='T'){
				dp[i+1][v]=min(dp[i+1][v],dp[i][v-1]+2);
				if(i>0&&s[i-1]=='A')dp[i+1][v]=min(dp[i+1][v],dp[i-1][v-1]+1);
			}else{//G
				dp[i+1][v]=min(dp[i+1][v],dp[i][v-1]+2);
				if(i>=2&&s[i-1]=='T'&&s[i-2]=='A')dp[i+1][v]=min(dp[i+1][v],dp[i-2][v-1]);
				if(i>=1&&s[i-1]=='T')dp[i+1][v]=min(dp[i+1][v],dp[i-1][v-1]+1);
				if(i>=1&&s[i-1]=='A')dp[i+1][v]=min(dp[i+1][v],dp[i-1][v-1]+1);
			}
		}
		// s[i] not part of a match
		for(int v=0;v<=i;v++)
		for(int le=1;le<=min(i+1,3);le++)
		dp[i+1][v]=min(dp[i+1][v],dp[i+1-le][v]+3-le);
	}
	int ans=1e9;
	for(int le=0;le<=n;le++)for(int v=0;v<=min(k,n);v++){
		ans=min(ans,dp[le][v]+3*(k-v));
	}
	cout<<ans<<endl;
}
