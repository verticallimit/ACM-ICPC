#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

typedef long long ll;

int dp[20][2];//从左到右依次为len，是否含6
int num[20];
int l, r;

int dfs(int pos, int s6, bool limit, bool fzero) {
	if (pos == -1) return s6;
	if(!limit && !fzero && ~dp[pos][s6])return dp[pos][s6];
	int up = limit ? num[pos] : 9;
	ll ans = 0;
	for (int i = 0; i <= up; ++i) {
		int now6 = s6;
		if (s6 == 0) {
			if(i == 6) now6 = 1;
		}
		ans += dfs(pos-1, now6, limit && i == up, fzero && !i);
	}
	return (limit || fzero) ? ans : dp[pos][s6]= ans;
}

int cal(int n) {
	int len = 0;
	while (n) {
		num[len++] = n % 10;
		n /= 10;
	}
	return dfs(len - 1, 0, 1, 1);
}


int main() {
	memset(dp, -1, sizeof(dp));
	while (scanf("%d%d",&l,&r) != EOF) {
        printf("%d %d\n", cal(l), cal(r));
		printf("%d\n", cal(r) - cal(l-1));
	}
	return 0;
}
