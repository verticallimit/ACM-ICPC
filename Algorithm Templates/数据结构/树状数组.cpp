//单点更新 区间最大值
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 200005;

int n, m, b[N], v[N];

void add(int x, int val) {
	v[x] = val;
	while (x <= n) {
		b[x] = max(val, b[x]);
		x += (x & (-x));
	}
}

void init() {
	int a;
	memset(b, 0, sizeof(b));
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a);
		add(i, a);
	}
}

int query(int l, int r) {
	int ans = v[r];
	while (l != r) {
		for (r -= 1; r - (r&(-r)) >= l; r -= (r&(-r))) {
			ans = max(ans, b[r]);
		}
		ans = max(ans, v[r]);
	}
	return ans;
}

void solve() {
	int a, b;
	char o[10];

	for (int i = 0; i < m; i++) {
		scanf("%s%d%d", o, &a, &b);
		if (o[0] == 'U') add(a, b);
		else printf("%d\n", query(a, b));
	}
}

int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		init();
		solve();
	}
	return 0;
}

// 模板
int lowbit(int x)
{
    return x & (-x);
}
void modify(int x,int add)//一维
{
    while(x<=MAXN)
    {
        a[x]+=add;
        x+=lowbit(x);
    }
}
int get_sum(int x) //求前x项的和
{
    int ret=0;
    while(x!=0)
    {
        ret+=a[x];
        x-=lowbit(x);
    }
    return ret;
}
void modify(int x,int y,int data)//二维
{
    for(int i=x;i<MAXN;i+=lowbit(i))
        for(int j=y;j<MAXN;j+=lowbit(j))
            a[i][j]+=data;
}
int get_sum(int x,int y)
{
    int res=0;
    for(int i=x;i>0;i-=lowbit(i))
        for(int j=y;j>0;j-=lowbit(j))
            res+=a[i][j];
    return res;
}
