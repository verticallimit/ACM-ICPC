#include<iostream>  
#include<cstdio>  
#include<cmath>  
#include<cstring>  
#define ll long long  
using namespace std;

const int mod = 201829;

struct matrix
{
	ll f[5][5];
	matrix operator* (const matrix &a) const {
		matrix res;
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				res.f[i][j] = 0;
				for (int k = 1; k <= 4; k++)
					res.f[i][j] = (res.f[i][j] + (*this).f[i][k] * a.f[k][j]) % mod;
				res.f[i][j] = (res.f[i][j] % mod + mod) % mod;
			}
		}
		return res;
	}
}a, b;

void init()
{
	b.f[1][1] = 1, b.f[1][2] = 2, b.f[1][4] = 1;
	b.f[2][1] = 1;
	b.f[3][2] = 1;
	b.f[4][4] = 1;
	a.f[1][1] = 2, a.f[2][1] = 1, a.f[3][1] = 0, a.f[4][1] = 1;
}

matrix fast_pow(matrix &base, int k)
{
	matrix ans = base;
	while (k) {
		if (k & 1)
			ans = ans*base;
		base = base*base;
		k >>= 1;
	}
	return ans;
}
int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		if (n == 0) break;
		if (n == 1) { printf("%d\n", 1); continue; }
		if (n == 2) { printf("%d\n", 2); continue; }
		n -= 3;
		init();
		struct matrix cur, ans;
		cur = b;
		cur = fast_pow(cur, n);
		ans = cur*a;
		printf("%lld\n", ans.f[1][1]);
	}
	return 0;
}
