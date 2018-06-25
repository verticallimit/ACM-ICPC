#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

typedef long long ll;

ll dp[20][2];//从左到右依次为len，是否含6
ll num[20];
ll l, r;

ll dfs(ll pos, ll s6, bool limit, bool fzero) {
	if (pos == -1) return s6;
	if(!limit && !fzero && ~dp[pos][s6])return dp[pos][s6];
	ll up = limit ? num[pos] : 9;
	ll ans = 0;
	for (ll i = 0; i <= up; ++i) {
		ll now6 = s6;
		if (s6 == 0) {
			if(i == 6) now6 = 1;
		}
		ans += dfs(pos-1, now6, limit && i == up, fzero && !i);
	}
	return (limit || fzero) ? ans : dp[pos][s6]= ans;
}

ll cal(ll n) {
	ll len = 0;
	while (n) {
		num[len++] = n % 10;
		n /= 10;
	}
	return dfs(len - 1, 0, 1, 1);
}


int main() {
    freopen("C:\\Users\\Administrator\\Desktop\\省赛题目\\F\\1.in", "r", stdin);
    freopen("C:\\Users\\Administrator\\Desktop\\省赛题目\\F\\1.out", "w", stdout);
	memset(dp, -1, sizeof(dp));
	while (scanf("%lld%lld",&l,&r) != EOF) {
		printf("%lld\n", cal(r) - cal(l-1));
	}
	return 0;
}
